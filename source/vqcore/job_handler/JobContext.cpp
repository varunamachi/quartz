

#include <QReadWriteLock>

#include "JobContext.h"



namespace Vam {

class JobContext::Impl
{
public:
    explicit Impl( JobContext::JobProgressCallback callback )
        : m_callback( callback )
        , m_cancelRequested( false )
    {

    }

    inline bool cancelRequested() const
    {
        m_lock.lockForRead();
        return m_cancelRequested;
    }

    inline void requestCancel()
    {
        m_lock.lockForWrite();
        m_cancelRequested = true;
    }

    JobContext::JobProgressCallback progressCallback()
    {
        return m_callback;
    }

private:
    JobContext::JobProgressCallback m_callback;

    bool m_cancelRequested;

    mutable QReadWriteLock m_lock;
};



JobContext::JobContext( JobContext::JobProgressCallback callback )
    : m_impl( std::make_unique< JobContext::Impl >( callback ))
{

}


bool JobContext::cancelRequested() const
{
    return m_impl->cancelRequested();
}


void JobContext::requestCancel()
{
    return m_impl->requestCancel();
}


void JobContext::setProgress( int totalMilestones,
                              int milestonesCompleted,
                              int currentMilestoneProgress )
{
    auto progFunc = m_impl->progressCallback();
    progFunc( totalMilestones, milestonesCompleted, currentMilestoneProgress );
}


}
