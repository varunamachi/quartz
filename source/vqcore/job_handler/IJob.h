#pragma once

#include <vqcore/VQCommon.h>
#include <vqcore/common/Result.h>

namespace Vam {

class JobContext;

VQ_INTERFACE IJob
{
    virtual Result< bool > execute( const JobContext &context ) = 0;

    virtual ~IJob() { }
};

}
