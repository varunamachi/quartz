#pragma once

#include <memory>

#include "../VQCommon.h"
#include "IJob.h"

namespace Vam {

class JobSequence;


class JobHandler final
{
public:
    JobHandler();

    void addJob( std::unique_ptr< IJob > job );

    void addJob( IJob::JobFunc jobFunc );

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;

};

}
