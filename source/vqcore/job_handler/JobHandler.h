#pragma once

#include <memory>

#include "IJob.h"

namespace Vq {

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
