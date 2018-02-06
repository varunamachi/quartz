
#include "HttpRequest.h"

namespace Quartz { namespace Http {

struct HttpRequest::Data
{

};

HttpRequest::HttpRequest()
    : m_data{ new Data{} }
{

}

HttpRequest::~HttpRequest()
{

}

} }
