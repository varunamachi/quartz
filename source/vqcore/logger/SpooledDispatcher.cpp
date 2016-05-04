
#include <thread>

#include <QString>
#include <QReadWriteLock>
#include <QQueue>

#include "../common/ScopedOperation.h"
#include "SpooledDispatcher.h"
#include "LogMessage.h"



namespace Vam { namespace Logger {

struct SpooledDispatcher::Data
{
    Data()
        : m_thread()
        , m_stop( true )
    {

    }

    std::thread m_thread;

    bool m_stop;

    QQueue< LogMessage *> m_logQueue;

    QReadWriteLock m_logIoLock;
};


void SpooledDispatcher::stopDispatch()
{
    m_data->m_stop = true;
}


SpooledDispatcher::SpooledDispatcher()
    : m_data( std::make_unique< Data >() )
{

}


SpooledDispatcher::~SpooledDispatcher()
{
    m_data->m_stop = true;
    while( ! m_data->m_thread.joinable() );
}

void SpooledDispatcher::write(LogMessage *message)
{
    if( m_data->m_stop ) {
        m_data->m_stop = false;
        m_data->m_thread = std::thread( &SpooledDispatcher::run, this );
    }
    SCOPE_LIMIT( m_data->m_logIoLock.lockForWrite(),
                 m_data->m_logIoLock.unlock() );
    m_data->m_logQueue.append( message );
}


void SpooledDispatcher::run()
{
    while( ! m_data->m_stop ) {
        m_data->m_logIoLock.lockForRead();
        bool hasMsgs = ! m_data->m_logQueue.isEmpty();
        m_data->m_logIoLock.unlock();
        if( hasMsgs ) {
            m_data->m_logIoLock.lockForWrite();
            auto msg = m_data->m_logQueue.takeLast();
            AT_SCOPE_EXIT( delete msg );
            m_data->m_logIoLock.unlock();
            writeToTargets( msg );
        }
    }
}

} }
