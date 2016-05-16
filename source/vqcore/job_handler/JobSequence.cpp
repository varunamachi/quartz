
#include <deque>
#include <mutex>
#include <thread>

#include "../common/Threading.h"
#include "JobSequence.h"

namespace Vam {

class JobSequence::Impl
{
public:
    void addJob( IJob::JobFunc jobFunc )
    {
        VQ_LOCK( m_mutex );
        m_sequence.push_front( jobFunc );
    }

    IJob::JobFunc takeNext()
    {
        IJob::JobFunc func = nullptr;
        VQ_LOCK( m_mutex );
        if( ! m_sequence.empty() ) {
            func = m_sequence.back();
            m_sequence.pop_back();
        }
        return func;
    }

    bool hasJob() const
    {
        VQ_LOCK( m_mutex );
        bool result = ! m_sequence.empty();
        return result;
    }

private:
    std::deque< IJob::JobFunc > m_sequence;

    mutable std::mutex m_mutex;
};


Result< bool > JobSequence::execute( const JobContext &context )
{
    Result< bool > result;
    auto jobFunc = m_impl->takeNext();
    if( jobFunc != nullptr ) {
        result = jobFunc( context );
    }
    else {
        result = Result< bool >::failure( "Invalid job found" );
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

