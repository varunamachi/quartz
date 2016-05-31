#pragma once

#include <functional>

#include "../common/Macros.h"
#include "../common/Result.h"

namespace Vq {

class JobContext;

VQ_INTERFACE IJob
{
    using JobFunc = std::function< Result< bool >( const JobContext &context )>;

    virtual Result< bool > execute( const JobContext &context ) = 0;

    virtual ~IJob() { }
};

}
