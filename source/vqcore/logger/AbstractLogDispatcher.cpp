
#include <std::string>
#include <QList>
#include <QQueue>
#include <QHash>
#include <QReadWriteLock>

#include "../common/ScopedOperation.h"
#include "AbstractLogDispatcher.h"
#include "AbstractLogTarget.h"
#include "ILogFilter.h"

namespace Vq { namespace Logger {

struct TargetInfo
{
    using SPtr = std::shared_ptr< TargetInfo >;

    TargetInfo( std::unique_ptr< AbstractLogTarget > &&target, bool enable )
        : m_target( std::move( target ))
        , m_enabled( enable ) {}

    ~TargetInfo()
    {

    }

    std::unique_ptr< AbstractLogTarget > m_target;

    bool m_enabled;

    QList< std::shared_ptr< ILogFilter >> m_targetFilters;
};

struct FilterInfo
{
    FilterInfo( std::shared_ptr< ILogFilter > filter )
        : m_filter( filter )
        , m_refs( 0 )
        , m_enabled( true ) {}

    ~FilterInfo()
    {
    }

    std::shared_ptr< ILogFilter > m_filter;

    int m_refs;

    bool m_enabled;
};




class AbstractLogDispatcher::Impl
{
public:
    Impl();

    bool addTarget( std::unique_ptr< AbstractLogTarget > &&target );

    AbstractLogTarget * target( const std::string &targetId );

    bool setTargetEnabledState( const std::string &trgId, bool value );

    bool removeTarget( const std::string &targetId );

    bool installFilter( std::shared_ptr< ILogFilter > filter,
                        const std::string &trgtId );

    bool uninstallFilter( const std::string &filterId,
                          const std::string &trgtId );

    void flush();

    void writeToTargets( LogMessage *message );

    ~Impl();

private:
    QHash< std::string, std::shared_ptr< FilterInfo >> m_allFilters;

    QHash< std::string, std::shared_ptr< TargetInfo >> m_targets;

    mutable QReadWriteLock m_lock;
};


AbstractLogDispatcher::Impl::Impl()
{

}


bool AbstractLogDispatcher::Impl::addTarget(
        std::unique_ptr< AbstractLogTarget > &&target )
{
    bool result = false;
    if( target != nullptr && ! m_targets.contains( target->uniqueId() )) {
        SCOPE_LIMIT( m_lock.lockForWrite(), m_lock.unlock() );
        m_targets.insert( target->uniqueId(),
                          std::make_shared< TargetInfo >( std::move( target ),
                                                          true ));
        result = true;
    }
    return result;
}


AbstractLogTarget * AbstractLogDispatcher::Impl::target(
        const std::string &targetId )
{
    auto &info = m_targets.value( targetId );
    return info != nullptr ? info->m_target.get() : nullptr;
}


bool AbstractLogDispatcher::Impl::setTargetEnabledState(
        const std::string &trgId,
        bool value )
{
    bool result = false;
    auto &info = m_targets.value( trgId );
    if( info != nullptr ) {
        SCOPE_LIMIT( m_lock.lockForWrite(), m_lock.unlock() );
        info->m_enabled = value;
        result = true;
    }
    return result;
}


bool AbstractLogDispatcher::Impl::removeTarget( const std::string &targetId )
{
    bool result = false;
    auto info = m_targets.value( targetId );
    if( info != nullptr ) {
        foreach( auto filter, info->m_targetFilters ) {
            if( m_allFilters.value( filter->filterId() )->m_refs == 1 ) {
                SCOPE_LIMIT( m_lock.lockForWrite(), m_lock.unlock() );
                m_allFilters.remove( filter->filterId() );
            }
        }
        SCOPE_LIMIT( m_lock.lockForWrite(), m_lock.unlock() );
        m_targets.remove( targetId );
        result = true;
    }
    return result;
}


bool AbstractLogDispatcher::Impl::installFilter(
        std::shared_ptr< ILogFilter > filter,
        const std::string &targetId )
{
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
