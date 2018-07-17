
#include "HttpResponse.h"
#include "Common.h"

namespace Quartz { namespace Http {

struct HttpResponse::Data
{
    Data( const QString &version,
          StatusCode status )
        : m_version{ version }
        , m_status{ status }
    {

    }

    QString m_version;

    StatusCode m_status;

    Headers m_headers;

    QByteArray m_body;
};

HttpResponse::HttpResponse( const QString &version, StatusCode status )
    : m_data{ new Data{ version, status }}
{

}

HttpResponse::~HttpResponse()
{

}

const QString &HttpResponse::version() const
{
    return m_data->m_version;
}

StatusCode HttpResponse::status() const
{
    return m_data->m_status;
}

QString HttpResponse::header( const QString &key ) const
{
    return m_data->m_headers.value( key );
}

bool HttpResponse::hasHeader(const QString &key) const
{
    return m_data->m_headers.contains( key );
}

void HttpResponse::setHeader(const QString &key, const QString &value)
{
    m_data->m_headers[ key ] = value;
}

void HttpResponse::setRedirect( const QString &url )
{
    this->setHeader( "location", url );
    this->m_data->m_status = StatusCode::FOUND;
}

void HttpResponse::setContent(
        const QByteArray &content,
        const QString &contentType )
{
    this->m_data->m_body = content;
    this->setHeader( "Content-Type", contentType );
}

} }
