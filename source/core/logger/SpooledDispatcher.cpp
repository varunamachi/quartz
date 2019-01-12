
#include <thread>

#include <QString>
#include <queue>


#include "../utils/ScopedOperation.h"
#include "../utils/Threading.h"
#include "SpooledDispatcher.h"
#include "LogMessage.h"



namespace Quartz { namespace Logger {

struct SpooledDispatcher::Data
{
    Data()
        : m_thread()
        , m_stop(false)
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
    m_data->m_thread.join();
    flushQueue();
}


SpooledDispatcher::SpooledDispatcher()
//    : m_data(std::make_unique<Data>())
    : m_data(std::make_unique<Data>())
{
    m_data->m_thread = std::thread(&SpooledDispatcher::run, this);
}


SpooledDispatcher::~SpooledDispatcher()
{
    m_data->m_stop = true;
    m_data->m_thread.join();
}

void SpooledDispatcher::write(LogMessage *message)
{
    if (m_data->m_stop) {
        m_data->m_stop = false;
        m_data->m_thread = std::thread(&SpooledDispatcher::run, this);
    }
    VQ_LOCK(m_data->m_logIoMutex);
    m_data->m_logQueue.emplace(message);
}


void SpooledDispatcher::run()
{
    while (! m_data->m_stop) {
        if (!  m_data->m_logQueue.empty()) {
            VQ_LOCK(m_data->m_logIoMutex);
            if (! m_data->m_logQueue.empty()) {
                auto msg = m_data->m_logQueue.front();
                AT_SCOPE_EXIT(delete msg);
                m_data->m_logQueue.pop();
                writeToTargets(msg);
            }
        }
        else {
            std::this_thread::sleep_for (std::chrono::milliseconds(100));
        }
    }
}

void SpooledDispatcher::flushQueue()
{
    VQ_LOCK(m_data->m_logIoMutex);
    while (!  m_data->m_logQueue.empty()) {
        auto msg = m_data->m_logQueue.front();
        AT_SCOPE_EXIT(delete msg);
        m_data->m_logQueue.pop();
        writeToTargets(msg);
    }
}

} }
