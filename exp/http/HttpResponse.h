#pragma once

#include <memory>

namespace Quartz { namespace Http {

class HttpResponse
{
public:
    HttpResponse();

    ~HttpResponse();

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

} }
