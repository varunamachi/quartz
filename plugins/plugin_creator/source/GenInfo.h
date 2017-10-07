#pragma once

#include <memory>

namespace Quartz { namespace Plugin { namespace Creator {

class GenInfo
{
public:
    GenInfo();

    ~GenInfo();

private:
    struct Data;
    std::unique_ptr< Data > m_data;


};

} } }
