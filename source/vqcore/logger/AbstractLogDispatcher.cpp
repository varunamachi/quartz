
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

//#include <QList>
//#include <QQueue>
//#include <QHash>
//#include <QReadWriteLock>

#include "../common/ScopedOperation.h"
#include "../common/Threading.h"
#include "../common/STLUtils.h"
#include "AbstractLogDispatcher.h"
#include "AbstractLogTarget.h"
#include "ILogFilter.h"

namespace Vq { namespace Logger {


namespace {

using FilterPtrUq = std::unique_ptr< ILogFilter >;
using TargetPtrUq = std::unique_ptr< AbstractLogTarget >;

class TargetInfo
{
public:
    VQ_NO_COPY( TargetInfo );

    inline TargetInfo( TargetPtrUq &&target, bool enable )
        : m_target( std::move( target ))
        , m_enabled( enable )
    {

    }

    inline TargetInfo( TargetInfo &&other )
        : m_target ( std::move( other.m_target )),
          m_enabled ( other.m_enabled ),
          m_targetFilters ( std::move( other.m_targetFilters ))
    {

    }

    inline TargetInfo & operator = ( TargetInfo &&other )
    {
        m_target = std::move( other.m_target );
        m_enabled = other.m_enabled;
        m_targetFilters = std::move( other.m_targetFilters );
        return *this;
    }

    ~TargetInfo()
    {

    }

    inline AbstractLogTarget * target() const
    {
        return m_target.get();
    }

    inline bool enabled() const
    {
        return m_enabled;
    }

    inline void setEnabled( bool value )
    {
        m_enabled = value;
    }

    inline std::vector< ILogFilter * > & filters()
    {
        return m_targetFilters;
    }

private:
    TargetPtrUq m_target;

    bool m_enabled;

    std::vector< ILogFilter * > m_targetFilters;
};



class FilterInfo
{
public:
    VQ_NO_COPY( FilterInfo );

    inline explicit FilterInfo( FilterPtrUq filter )
        : m_filter( std::move( filter ))
        , m_refs( 0 )
        , m_enabled( true )
    {

    }

    inline FilterInfo( FilterInfo &&other )
        : m_filter( std::move( other.m_filter ))
        , m_refs( other.refs() )
        , m_enabled( other.m_enabled )
    {

    }

    inline FilterInfo & operator = ( FilterInfo &&other )
    {
        m_filter = std::move( other.m_filter );
        m_refs = other.m_refs;
        m_enabled = other.m_enabled;
        return *this;
    }

    inline ILogFilter * filter()
    {
        return m_filter.get();
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

    inline void setEnabled( bool value )
    {
        m_enabled = value;
    }

    ~FilterInfo()
    {
    }


private:
    FilterPtrUq m_filter;

    int m_refs;

    bool m_enabled;
};

} //End private namespace



class AbstractLogDispatcher::Impl
{
public:
    Impl();

    bool addTarget( TargetPtrUq &&target );

    AbstractLogTarget * target( const std::string &targetId );

    bool setTargetEnabledState( const std::string &trgId, bool value );

    bool removeTarget( const std::string &targetId );

    bool installFilter( FilterPtrUq filter,
                        const std::string &trgtId );

    bool uninstallFilter( const std::string &filterId,
                          const std::string &trgtId );

    void flush();

    void writeToTargets( LogMessage *message );

    ~Impl();

private:
    std::unordered_map< std::string, FilterInfo > m_allFilters;

    std::unordered_map< std::string, TargetInfo > m_targets;

    mutable std::mutex m_mutex;

};


AbstractLogDispatcher::Impl::Impl()
{

}


bool AbstractLogDispatcher::Impl::addTarget(
        std::unique_ptr< AbstractLogTarget > &&target )
{
    bool result = false;
    if( target != nullptr
            && ! STLUtils::contains( m_targets, target->uniqueId() )) {
        VQ_LOCK( m_mutex );
        m_targets.emplace( target->uniqueId(),
                           TargetInfo( std::move( target ), true ));
        result = true;
    }
    return result;
}


AbstractLogTarget * AbstractLogDispatcher::Impl::target(
        const std::string &targetId )
{
    AbstractLogTarget *target = nullptr;
    auto it = m_targets.find( targetId );
    if( it != std::end( m_targets )) {
        auto &targetInfoPtr = it->second;
        target = targetInfoPtr.target();

    }
    return target;
}


bool AbstractLogDispatcher::Impl::setTargetEnabledState(
        const std::string &trgId,
        bool value )
{
    bool result = false;
    auto it = m_targets.find( trgId );
    if( it != std::end( m_targets )) {
        VQ_LOCK( m_mutex );
        auto & trgInfo = it->second;
        trgInfo.setEnabled( value );
        result = true;
    }
    return result;
}


bool AbstractLogDispatcher::Impl::removeTarget( const std::string &targetId )
{

    bool result = false;
    auto it = m_targets.find( targetId );
    if( it != std::end( m_targets )) {
        auto &info = it->second;
        for( auto &filter : info.filters() ) {
            VQ_LOCK( m_mutex );
            m_allFilters.erase( filter->filterId() );
        }
        VQ_LOCK( m_mutex );
        m_targets.erase( targetId );
    }
    return result;
}


bool AbstractLogDispatcher::Impl::installFilter(
        std::unique_ptr< ILogFilter > filter,
        const std::string &targetId )
{
    if( ! filter ) {
        return false;
    }
    auto getFilterInfo = [ & ]() -> FilterInfo &
    {
        auto it = m_allFilters.find( filter->filterId() );
        if( it == std::end( m_allFilters ))  {
            m_allFilters.emplace( filter->filterId(),
                                  FilterInfo( std::move( filter )));
            return m_allFilters.find( filter->filterId() )->second;
        }
        return it->second;
    };

    bool result = false;

    if( targetId.empty() ) {
        VQ_LOCK( m_mutex );
        auto &finfo = getFilterInfo();
        for( auto &tpair : m_targets ) {
            auto &tinfo = tpair.second;
            if( STLUtils::contains( tinfo.filters(), filter )) {

            }
        }


        SCOPE_LIMIT( m_lock.lockForWrite(), m_lock.unlock() );
        auto finfo = getFilterInfo();
        if( finfo != nullptr ) {
            for( auto it = m_targets.begin();
                 it != m_targets.end();
                 ++ it ) {
                auto sinfo = it.value();
                if( ! sinfo->m_targetFilters.contains( filter )) {
                    sinfo->m_targetFilters.append( filter );
                    ++ finfo->m_refs;
                }
            }
            result = true;
        }
    }



    bool result = false;
    if( filter ) {
        auto getFilterInfo = [ = ]() -> std::shared_ptr< FilterInfo >
        {
            auto fltInfo = m_allFilters.value( filter->filterId() );
            if( fltInfo == nullptr ) {
                fltInfo = std::make_shared< FilterInfo >( filter );
                m_allFilters.insert( filter->filterId(), fltInfo );
            }
            else if( filter != fltInfo->m_filter ){
                /** We are registering two different filter instances with same
                 * filter id. In this case the correct way is to get the filter
                 * instance for the given id from the dispatcher and install
                 * the same instance again.
                 */
                fltInfo = 0;
            }
            return fltInfo;
        };

        if( targetId.isEmpty() ) {
            SCOPE_LIMIT( m_lock.lockForWrite(), m_lock.unlock() );
            auto finfo = getFilterInfo();
            if( finfo != nullptr ) {
                for( auto it = m_targets.begin();
                     it != m_targets.end();
                     ++ it ) {
                    auto sinfo = it.value();
                    if( ! sinfo->m_targetFilters.contains( filter )) {
                        sinfo->m_targetFilters.append( filter );
                        ++ finfo->m_refs;
                    }
                }
                result = true;
            }
        }
        else if( m_targets.contains( targetId )){
            auto sinfo = m_targets.value( targetId );
            if( sinfo != nullptr ) {
                SCOPE_LIMIT( m_lock.lockForWrite(), m_lock.unlock() );
                auto finfo = getFilterInfo();
                if( finfo != nullptr ) {
                    if( ! sinfo->m_targetFilters.contains( filter )) {
                        sinfo->m_targetFilters.append( filter );
                        ++ finfo->m_refs;
                    }
                    result = true;
                }
            }
        }
    }
    return result;
}


bool AbstractLogDispatcher::Impl::uninstallFilter( const std::string &filterId,
                                                   const std::string &targetId )
{
    bool result = false;
    auto finfo = m_allFilters.value( filterId );
    if( finfo != nullptr ) {
        if( targetId.isEmpty() ) {
            int numRemoved = 0;
            SCOPE_LIMIT( m_lock.lockForWrite(), m_lock.unlock() );
            for( auto sit = m_targets.begin(); sit != m_targets.end(); ++ sit ){
                auto sinfo = sit.value();
                if( sinfo->m_targetFilters.removeOne( finfo->m_filter )) {
                    ++ numRemoved;
                }
            }
            result = numRemoved != 0;
        }
        else {
            auto sinfo = m_targets.value( targetId );
            if( sinfo != nullptr ) {
                SCOPE_LIMIT( m_lock.lockForWrite(), m_lock.unlock() );
                result = true;
                if( sinfo->m_targetFilters.removeOne( finfo->m_filter )) {
                    -- finfo->m_refs;
                    if( finfo->m_refs == 0 ) {
                        m_allFilters.remove( filterId );
                    }
                }

            }
        }
    }
    return result;
}


void AbstractLogDispatcher::Impl::flush()
{
    SCOPE_LIMIT( m_lock.lockForWrite(), m_lock.unlock() );
    for( auto sit = m_targets.begin(); sit != m_targets.end(); ++ sit ) {
        auto sinfo = sit.value();
        sinfo->m_target->flush();
    }
}


void AbstractLogDispatcher::Impl::writeToTargets( LogMessage *message )
{
    SCOPE_LIMIT( m_lock.lockForRead(), m_lock.unlock() );
    for( auto sit = m_targets.begin(); sit != m_targets.end(); ++ sit ) {
        auto sinfo = sit.value();
        if( sinfo->m_enabled ) {
            bool filteredOut = false;
            foreach( auto filter, sinfo->m_targetFilters ) {
                auto finfo = m_allFilters.value( filter->filterId() );
                if( finfo->m_enabled ) {
                    filteredOut = filter->filterOut( message );
                    if( filteredOut ) {
                        break;
                    }
                }
            }
            if( ! filteredOut ) {
                sinfo->m_target->write( message );
            }
        }
    }
}


AbstractLogDispatcher::Impl::~Impl()
{
    flush();
}



//======================= AbstractLogDispatcher ===============================
AbstractLogDispatcher::AbstractLogDispatcher()
    : m_impl( std::make_unique< Impl >() )
{

}


bool AbstractLogDispatcher::addTarget(
        std::unique_ptr< AbstractLogTarget > &&target )
{
    return m_impl->addTarget( std::move( target ));
}


AbstractLogTarget * AbstractLogDispatcher::target( std::string targetId )
{
    return m_impl->target( targetId );
}


bool AbstractLogDispatcher::setTargetEnabledState( const std::string &trgId,
                                                   bool value )
{
    return m_impl->setTargetEnabledState( trgId, value );
}


bool AbstractLogDispatcher::removeTarget( const std::string &targetId )
{
    return m_impl->removeTarget( targetId );
}


bool AbstractLogDispatcher::installFilter( std::shared_ptr< ILogFilter > filter,
                    const std::string &trgtId )
{
    return m_impl->installFilter( filter, trgtId );
}


bool AbstractLogDispatcher::uninstallFilter( const std::string &filterId,
                      const std::string &trgtId )
{
    return m_impl->uninstallFilter( filterId, trgtId );
}


void AbstractLogDispatcher::flush()
{
    m_impl->flush();
}

void AbstractLogDispatcher::writeToTargets( LogMessage *msg )
{
    m_impl->writeToTargets( msg );
}

AbstractLogDispatcher::~AbstractLogDispatcher()
{

}






} }
