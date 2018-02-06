#pragma once

#include <memory>

#include <QObject>

namespace Quartz { namespace Http {

class HttpServer : public QObject {
    Q_OBJECT
public:
    explicit HttpServer( QObject *parent = nullptr );

    ~HttpServer();

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

} }
