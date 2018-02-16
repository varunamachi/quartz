
#include "Constants.h"
#include "HttpRequest.h"
#include "MultipartFile.h"

namespace Quartz { namespace Http {

struct HttpRequest::Data
{
    Data( const QString &version, Method method, const QString &path )
        : m_version{ version }
        , m_method{ method }
        , m_path{ path }
    {

    }

    QString m_version;

    Method m_method;

    QString m_path;

    Headers m_headers;

    QByteArray m_body;

    Param m_params;

    QHash< QString, std::shared_ptr< MultipartFile >> m_files;

    ProgFunc m_progCallback;

};

HttpRequest::HttpRequest(
        const QString &version,
        Method method,
        const QString &path )
    : m_data{ new Data{ version, method, path }}
{

}

HttpRequest::~HttpRequest()
{

}

void HttpRequest::setHeader( const QString &key, const QString &value )
{
    m_data->m_headers.insert( key, value );
}

QString HttpRequest::header( const QString key ) const
{
    return m_data->m_headers.value( key );
}

const QString & HttpRequest::version() const
{
    return m_data->m_version;
}

Method HttpRequest::method() const
{
    return m_data->m_method;
}

const QString & HttpRequest::path() const
{
    return m_data->m_path;
}

ProgFunc HttpRequest::progress() const
{
    return m_data->m_progCallback;
}

QString HttpRequest::param( const QString &key ) const
{
    return m_data->m_params.value( key );
}

bool HttpRequest::hasFile( const QString &key ) const
{
    return m_data->m_files.contains( key );
}

const MultipartFile * HttpRequest::multipartFile( const QString name ) const
{
    MultipartFile *file = nullptr;
    if( m_data->m_files.contains( name )) {
        file = m_data->m_files.value( name ).get();
    }
    return file;
}

QByteArray & HttpRequest::body()
{
    return m_data->m_body;
}

} }
