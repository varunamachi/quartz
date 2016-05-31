#pragma once

#include <memory>

#include "IJob.h"

namespace Vq {

class Job : public IJob
{
public:
    explicit Job( JobFunc func );

    Result< bool > execute( const JobContext &context );

private:
    class Data;
    std::unique_ptr< Data > m_data;
};

}
