#pragma once

#include <memory>

namespace Quartz { namespace Http {

class HttpRequest
{
public:
    HttpRequest();

    ~HttpRequest();

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

} }
