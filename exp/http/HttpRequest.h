#pragma once

#include <QString>

#include <memory>

namespace Quartz { namespace Http {

class HttpRequest
{
public:
    HttpRequest( );

    ~HttpRequest();

    void addHeader( const QString &key, const QString &value );

    QString header( const QString key ) const;



private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

} }
