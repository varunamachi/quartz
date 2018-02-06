

#include "HttpClient.h"

namespace Quartz { namespace Http {

struct HttpClient::Data {

};

HttpClient::HttpClient( QObject *parent )
    : QObject{ parent }
    , m_data{ new Data{} }
{

}

HttpClient::~HttpClient()
{

}


} }
