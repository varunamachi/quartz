
#include "Constants.h"
#include "HttpRequest.h"

namespace Quartz { namespace Http {

struct HttpRequest::Data
{
    QString m_version;

    Method m_method;

    QString m_path;

    Headers m_headers;

    QByteArray m_body;

    Param m_params;

    MultipartFiles m_files;

    ProgFunc m_progCallback;

};

HttpRequest::HttpRequest()
    : m_data{ new Data{} }
{

}

HttpRequest::~HttpRequest()
{

}

void HttpRequest::addHeader( const QString &key, const QString &value )
{

}

QString HttpRequest::header( const QString key ) const
{

}

} }
