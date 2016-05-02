#pragma once

#include <memory>

#include "IJob.h"

namespace Vam {

class Job : public IJob
{
public:
    using JobFunc = std::function< void( const JobContext &context )>;

    explicit Job( JobFunc func );

    Result< bool > execute(const JobContext &context);

private:
    class Data;
    std::unique_ptr< Data > m_data;
};

}
