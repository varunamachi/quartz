
#include "HttpResponse.h"

namespace Quartz { namespace Http {

struct HttpResponse::Data
{

};

HttpResponse::HttpResponse()
    : m_data{ new Data{} }
{

}

HttpResponse::~HttpResponse()
{

}

} }
