
#include "Job.h"

namespace Vam {

class Job::Data
{
public:
    inline explicit Data( IJob::JobFunc &func )
        : m_jobFunc( func )
    {

    }

    inline IJob::JobFunc jobFunc() const
    {
        return m_jobFunc;
    }

private:
    IJob::JobFunc m_jobFunc;
};


Job::Job( IJob::JobFunc func )
    : m_data( std::make_unique< Job::Data >( func ))
{

}


Result< bool > Job::execute( const JobContext &context )
{
    auto result = std::move( m_data->jobFunc()( context ));
    return result;
}

}
