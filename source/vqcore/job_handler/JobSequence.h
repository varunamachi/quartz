#pragma once

#include <memory>

#include "IJob.h"

namespace Vam {

class JobSequence : public IJob
{
public:
    Result< bool > execute( const JobContext &context );

    JobSequence & add( IJob::JobFunc jobFunc );

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;
};


}
