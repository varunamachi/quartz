#pragma once

#include <memory>

#include <QObject>

namespace Quartz { namespace Http {

class HttpClient : public QObject {
    Q_OBJECT
public:
    explicit HttpClient( QObject *parent = nullptr );

    ~HttpClient();

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

} }
