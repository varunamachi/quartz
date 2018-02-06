

#include "HttpServer.h"

namespace Quartz { namespace Http {

struct HttpServer::Data {

};

HttpServer::HttpServer( QObject *parent )
    : QObject{ parent }
    , m_data{ new Data{} }
{

}

HttpServer::~HttpServer()
{

}


} }
