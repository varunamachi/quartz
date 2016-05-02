
#include <QQueue>
#include <QReadWriteLock>

#include "JobSequence.h"

namespace Vam {

class JobSequence::Impl
{
public:
    void addJob( IJob::JobFunc jobFunc )
    {
        m_lock.lockForWrite();
        m_sequence.push_front( jobFunc );
    }

    IJob::JobFunc takeNext()
    {
        IJob::JobFunc func = nullptr;
        m_lock.lockForWrite();
        if( ! m_sequence.isEmpty() ) {
            func =m_sequence.takeLast();
        }
        return func;
    }

    bool hasJob() const
    {
        m_lock.lockForRead();
        return ! m_sequence.isEmpty();
    }

private:
    QQueue< IJob::JobFunc > m_sequence;

    mutable QReadWriteLock m_lock;


};


Result< bool > JobSequence::execute( const JobContext &context )
{
    Result< bool > result;
    auto jobFunc = m_impl->takeNext();
    if( jobFunc != nullptr ) {
        result = jobFunc( context );
    }
    else {
        result = Result< bool >::failure( tr( "Invalid job found" ));
    }
    return result;
}


JobSequence & JobSequence::add( IJob::JobFunc jobFunc )
{
    if( jobFunc ) {
        m_impl->addJob( jobFunc );
    }
    return *this;
}

}

