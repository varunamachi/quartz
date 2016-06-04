
#include <thread>

#include <string>
#include <queue>


#include "../common/ScopedOperation.h"
#include "../common/Threading.h"
#include "SpooledDispatcher.h"
#include "LogMessage.h"



namespace Vq { namespace Logger {

struct SpooledDispatcher::Data
{
    Data()
        : m_thread()
        , m_stop( true )
    {

    }

    std::thread m_thread;

    bool m_stop;

    std::queue< LogMessage *> m_logQueue;

    std::mutex m_logIoMutex;
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
    VQ_LOCK( m_data->m_logIoMutex );
    m_data->m_logQueue.emplace( message );
}


void SpooledDispatcher::run()
{
    while( ! m_data->m_stop ) {
        VQ_LOCK( m_data->m_logIoMutex );
        if( ! m_data->m_logQueue.empty() ) {
            auto msg = m_data->m_logQueue.front();
            AT_SCOPE_EXIT( delete msg );
            m_data->m_logQueue.pop();
            writeToTargets( msg );
        }
    }
}

} }
