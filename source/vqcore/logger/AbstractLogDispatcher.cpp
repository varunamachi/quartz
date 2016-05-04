
#include <QString>
#include <QList>
#include <QQueue>
#include <QHash>
#include <QReadWriteLock>

#include "../common/ScopedOperation.h"
#include "AbstractLogDispatcher.h"
#include "AbstractLogTarget.h"
#include "ILogFilter.h"

namespace Vam { namespace Logger {

struct TargetInfo
{
    using SPtr = std::shared_ptr< TargetInfo >;

    TargetInfo( std::unique_ptr< AbstractLogTarget > target, bool enable )
        : m_target( std::move( target ))
        , m_enabled( enable ) {}

    ~TargetInfo()
    {

    }

    std::unique_ptr< AbstractLogTarget > m_target;

    bool m_enabled;

    QList< ILogFilter *> m_targetFilters;
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

    bool addTarget( std::shared_ptr< AbstractLogTarget > target );

    AbstractLogTarget * target( const QString &targetId );

    bool setTargetEnabledState( const QString &trgId, bool value );

    bool removeTarget( const QString &targetId );

    bool installFilter( std::shared_ptr< ILogFilter > filter,
                        const QString &trgtId );

    bool uninstallFilter( const QString &filterId,
                          const QString &trgtId );

    void write( LogMessage *message );

    void flush();

    void stopDispatch();

    ~Impl();

private:
    bool m_stop;

    QQueue< LogMessage *> m_logQueue;

    QHash< QString, std::shared_ptr< FilterInfo >> m_allFilters;

    QHash< QString, std::shared_ptr< TargetInfo >> m_targets;

    QReadWriteLock m_lock;

    QReadWriteLock m_logIoLock;

    bool m_shouldStop;

};


AbstractLogDispatcher::Impl::Impl()
{
    m_shouldStop = true;
//    this->wait();
//    foreach( LogMessage *msg, m_logQueue ) {
//        writeToTargets( msg );
//    }
    flush();
}


bool AbstractLogDispatcher::Impl::addTarget(
        std::shared_ptr< AbstractLogTarget > target )
{
    bool result = false;
    if( target != nullptr && ! m_targets.contains( target->uniqueId() )) {
        SCOPE_LIMIT( m_lock.lockForWrite(), m_lock.unlock() );
        m_targets.insert( target->uniqueId(),
                          std::make_shared< TargetInfo >( target, true ));
        result = true;
    }
    return result;
}


AbstractLogTarget * AbstractLogDispatcher::Impl::target(
        const QString &targetId )
{
    auto &info = m_targets.value( targetId );
    return info != nullptr ? info->m_target.get() : nullptr;
}


bool AbstractLogDispatcher::Impl::setTargetEnabledState(
        const QString &trgId,
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


bool AbstractLogDispatcher::Impl::removeTarget( const QString &targetId )
{
    bool result = false;
    auto info = m_targets.value( targetId );
    if( info != nullptr ) {
        foreach( auto filter, info->m_targetFilters ) {
            if( m_allFilters.value( filter->filterId() )->m_refs == 1 ) {
                SCOPE_LIMIT( m_lock.lockForWrite(), m_lock.unlock() );
                m_allFilters.remove( filter->filterId() );
                delete filter;
            }
        }
        SCOPE_LIMIT( m_lock.lockForWrite(), m_lock.unlock() );
        m_targets.remove( targetId );
        delete info;
        result = true;
    }
    return result;
}


bool AbstractLogDispatcher::Impl::installFilter( std::shared_ptr< ILogFilter > filter, const QString &trgtId )
{

}


bool AbstractLogDispatcher::Impl::uninstallFilter( const QString &filterId, const QString &trgtId )
{

}


void AbstractLogDispatcher::Impl::write( LogMessage *message )
{

}


void AbstractLogDispatcher::Impl::flush()
{

}


void AbstractLogDispatcher::Impl::stopDispatch()
{

}


AbstractLogDispatcher::Impl::~Impl()
{

}


} }
