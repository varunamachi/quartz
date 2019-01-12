
#include <vector>
#include <queue>
#include <unordered_map>

#include <QString>
#include <QHash>

//#include <QList>
//#include <QQueue>
//#include <QHash>
//#include <QReadWriteLock>

#include "../utils/ScopedOperation.h"
#include "../utils/Threading.h"
#include "../utils/STLUtils.h"
#include "AbstractLogDispatcher.h"
#include "AbstractLogTarget.h"
#include "ILogFilter.h"

namespace Quartz { namespace Logger {


namespace {

using FilterPtrUq = std::unique_ptr<ILogFilter>;
using TargetPtrUq = std::unique_ptr<AbstractLogTarget>;

class TargetInfo
{
public:
    QZ_NO_COPY(TargetInfo);

    inline TargetInfo(AbstractLogTarget *target, bool enable)
        : m_target(target)
        , m_enabled(enable)
    {

    }

    inline TargetInfo(TargetInfo &&other)
        : m_target (std::move(other.m_target)),
          m_enabled (other.m_enabled),
          m_targetFilters (std::move(other.m_targetFilters))
    {

    }

    inline TargetInfo & operator = (TargetInfo &&other)
    {
        m_target = std::move(other.m_target);
        m_enabled = other.m_enabled;
        m_targetFilters = std::move(other.m_targetFilters);
        return *this;
    }

    ~TargetInfo()
    {

    }

    inline bool operator == (const TargetInfo &other)
    {
        auto result = (this == &other || m_target == other.m_target);
        return result;
    }

    inline bool operator != (const TargetInfo &other)
    {
        return ! (*this  == other);
    }

    inline AbstractLogTarget * target() const
    {
        return m_target;
    }

    inline bool enabled() const
    {
        return m_enabled;
    }

    inline void setEnabled(bool value)
    {
        m_enabled = value;
    }

    inline std::vector< ILogFilter * > & filters()
    {
        return m_targetFilters;
    }

private:
    AbstractLogTarget *m_target;

    bool m_enabled;

    std::vector< ILogFilter * > m_targetFilters;
};



class FilterInfo
{
public:
    QZ_NO_COPY(FilterInfo);

    inline explicit FilterInfo(ILogFilter *filter)
        : m_filter(filter)
        , m_refs(0)
        , m_enabled(true)
    {

    }

    inline FilterInfo(FilterInfo &&other)
        : m_filter(std::move(other.m_filter))
        , m_refs(other.refs())
        , m_enabled(other.m_enabled)
    {

    }

    inline FilterInfo & operator = (FilterInfo &&other)
    {
        m_filter = std::move(other.m_filter);
        m_refs = other.m_refs;
        m_enabled = other.m_enabled;
        return *this;
    }

    inline bool operator == (const FilterInfo &other)
    {
        auto result = this == &other || m_filter == other.m_filter;
        return result;
    }

    inline bool operator != (const FilterInfo &other)
    {
        return ! (*this  == other);
    }

    inline ILogFilter * filter()
    {
        return m_filter;
    }


    inline int & refs()
    {
        return m_refs;
    }

    inline int refs() const
    {
        return m_refs;
    }

    inline bool enabled() const
    {
        return m_enabled;
    }

    inline void setEnabled(bool value)
    {
        m_enabled = value;
    }

    ~FilterInfo()
    {
    }


private:
    ILogFilter *m_filter;

    int m_refs;

    bool m_enabled;
};

} //End private namespace



class AbstractLogDispatcher::Impl
{
public:
    Impl();

    ~Impl() noexcept;

    bool addTarget(AbstractLogTarget *target);

    bool addTarget(TargetPtrUq target);

    AbstractLogTarget * target(const QString &targetId);

    bool setTargetEnabledState(const QString &trgId, bool value);

    bool removeTarget(const QString &targetId);

    bool installFilter(ILogFilter *filter, const QString &trgtId);

    bool installFilter(FilterPtrUq filter, const QString &trgtId);

    bool uninstallFilter(const QString &filterId, const QString &trgtId);

    void flush();

    void writeToTargets(LogMessage *message);

    QHash< QString, std::shared_ptr<FilterInfo>> m_allFilters;

    QHash< QString, std::shared_ptr<TargetInfo>> m_targets;

    std::unordered_map< std::string,
                        std::unique_ptr<AbstractLogTarget>> m_ownedTargets;

    std::unordered_map< std::string,
                        std::unique_ptr<ILogFilter>> m_ownedFilters;

    mutable std::mutex m_mutex;

};


AbstractLogDispatcher::Impl::Impl()
{

}


bool AbstractLogDispatcher::Impl::addTarget(AbstractLogTarget *target)
{
    bool result = false;
    if (target != nullptr && ! m_targets.contains(target->uniqueId())) {
        VQ_LOCK(m_mutex);
        const auto &targetId = target->uniqueId();
        m_targets.insert(targetId,
                          std::make_shared<TargetInfo>(target, true));
        result = true;
    }
    return result;
}

bool AbstractLogDispatcher::Impl::addTarget(TargetPtrUq target)
{
    bool result = addTarget(target.get());
    if (result) {
        auto id = target->uniqueId().toStdString();
        m_ownedTargets.insert(std::make_pair(id, std::move(target)));
    }
    return result;
}


AbstractLogTarget * AbstractLogDispatcher::Impl::target(
        const QString &targetId)
{
    AbstractLogTarget *target = nullptr;
    if (m_targets.contains(targetId)) {
        auto &targetInfoPtr = m_targets.value(targetId);
        target = targetInfoPtr->target();

    }
    return target;
}


bool AbstractLogDispatcher::Impl::setTargetEnabledState(
        const QString &trgId,
        bool value)
{
    bool result = false;
    if (m_targets.contains(trgId)) {
        VQ_LOCK(m_mutex);
        auto & trgInfo = m_targets[ trgId ];
        trgInfo->setEnabled(value);
        result = true;
    }
    return result;
}


bool AbstractLogDispatcher::Impl::removeTarget(const QString &targetId)
{
    bool result = false;
    if (m_targets.contains(targetId)) {
        auto &info = m_targets[ targetId ];
        VQ_LOCK(m_mutex);
        for (auto &filter : info->filters()) {
            m_allFilters.remove(filter->filterId());
        }
        m_targets.remove(targetId);
        STLUtils::remove(m_ownedTargets, targetId.toStdString());
        result = true;
    }
    return result;
}


bool AbstractLogDispatcher::Impl::installFilter(ILogFilter *filter,
                                                 const QString &targetId)
{
    if (! filter) {
        return false;
    }
    auto getFilterInfo = [ & ]() -> FilterInfo &
    {
        if (m_allFilters.contains(filter->filterId()))  {
            const auto &filterId = filter->filterId();
            m_allFilters.insert(filterId,
                                 std::make_shared<FilterInfo>(
                                     std::move(filter)));
            return * m_allFilters[ filterId ];
        }
        return * m_allFilters[ filter->filterId() ];
    };

    bool result = false;
    auto &finfo = getFilterInfo();
    if (targetId.isEmpty()) {
        VQ_LOCK(m_mutex);
        for (auto it = m_targets.begin(); it != m_targets.end(); ++it) {
            auto &tinfo = it.value();
            if (! STLUtils::contains(tinfo->filters(), filter)) {
                tinfo->filters().emplace_back(filter);
                ++ finfo.refs();
            }
        }
        result = true;
    }
    else {
        if (m_targets.contains(targetId)) {
            auto &tinfo = m_targets[ targetId ];
            VQ_LOCK(m_mutex);
            if (! STLUtils::contains(tinfo->filters(), filter)) {
                tinfo->filters().emplace_back(filter);
                ++ finfo.refs();
            }
            //If the filter is already there, still its a success
            result = true;
        }
    }
                   return result;
                 }

bool AbstractLogDispatcher::Impl::installFilter(FilterPtrUq filter,
                                                 const QString &trgtId)
{
    bool result = installFilter(filter.get(), trgtId);
    if (result) {
        auto id = filter->filterId().toStdString();
        m_ownedFilters.insert(std::make_pair(id, std::move(filter)));
    }
    return result;
}


bool AbstractLogDispatcher::Impl::uninstallFilter(const QString &filterId,
                                                   const QString &targetId)
{
    bool result = false;
    if (m_allFilters.contains(filterId)) {
        auto &finfo = m_allFilters[ filterId ];
        if (targetId.isEmpty()) {
            VQ_LOCK(m_mutex);
            for (auto it = m_targets.begin(); it != m_targets.end(); ++ it) {
                auto &tinfo = it.value();
                STLUtils::remove(tinfo->filters(), finfo->filter());
                STLUtils::remove(m_ownedFilters, filterId.toStdString());
                result = true;
            }
        }
        else {
            if (m_targets.contains(targetId)) {
                auto &tinfo = m_targets[ targetId ];
                VQ_LOCK(m_mutex);
                STLUtils::remove(tinfo->filters(), finfo->filter());
                -- finfo->refs();
                if (finfo->refs() == 0) {
                    m_allFilters.remove(filterId);
                    STLUtils::remove(m_ownedFilters, filterId.toStdString());
                }
                result = true;
            }
        }
    }
    return result;
}


void AbstractLogDispatcher::Impl::flush()
{
    VQ_LOCK(m_mutex);
    for (auto it = m_targets.begin(); it != m_targets.end(); ++ it) {
        it.value()->target()->flush();
    }
}


void AbstractLogDispatcher::Impl::writeToTargets(LogMessage *message)
{
    auto isFilteredOut = [ this, &message ](TargetInfo &tinfo) -> bool
    {
        bool filteredOut = false;
        for (auto &filter : tinfo.filters()) {
            //Since filter is there, filter info must be there
            auto &finfo = m_allFilters.value(filter->filterId());
            if (finfo->enabled() && filter->filterOut(message)) {
                filteredOut = true;
                break;
            }
        }
        return filteredOut;
    };

    VQ_LOCK(m_mutex);
    for (auto it = m_targets.begin(); it != m_targets.end(); ++ it) {
        auto &tinfo = it.value();
        if (! isFilteredOut(*tinfo)) {
            tinfo->target()->write(message);
        }
    }
}


AbstractLogDispatcher::Impl::~Impl() noexcept
{
    try {
        flush();
    } catch(...) {
        //killit
    }
}



//======================= AbstractLogDispatcher ===============================
AbstractLogDispatcher::AbstractLogDispatcher()
//    : m_impl(std::make_unique<Impl>())
    : m_impl(new Impl{})
{

}


bool AbstractLogDispatcher::addTarget(
        std::unique_ptr<AbstractLogTarget> &&target)
{
    return m_impl->addTarget(std::move(target));
}

bool AbstractLogDispatcher::addTarget(AbstractLogTarget *target)
{
    return m_impl->addTarget(target);
}


AbstractLogTarget * AbstractLogDispatcher::target(QString targetId)
{
    return m_impl->target(targetId);
}


bool AbstractLogDispatcher::setTargetEnabledState(const QString &trgId,
                                                   bool value)
{
    return m_impl->setTargetEnabledState(trgId, value);
}


bool AbstractLogDispatcher::removeTarget(const QString &targetId)
{
     return m_impl->removeTarget(targetId);
}

bool AbstractLogDispatcher::installFilter(ILogFilter *filter,
                                           const QString &targetId)
{
    return m_impl->installFilter(filter, targetId);
}


bool AbstractLogDispatcher::installFilter(FilterPtrUq &&filter,
                                           const QString &trgtId)
{
    return m_impl->installFilter(std::move(filter), trgtId);
}


bool AbstractLogDispatcher::uninstallFilter(const QString &filterId,
                      const QString &trgtId)
{
    return m_impl->uninstallFilter(filterId, trgtId);
}


void AbstractLogDispatcher::flush()
{
    m_impl->flush();
}

void AbstractLogDispatcher::writeToTargets(LogMessage *msg)
{
    m_impl->writeToTargets(msg);
}

AbstractLogDispatcher::~AbstractLogDispatcher()
{

}

} }
