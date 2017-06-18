#pragma once

#include <memory>

#include <QObject>

namespace Quartz {

class RestClient : public QObject
{
    Q_OBJECT
public:
    explicit RestClient( QObject *parent );

    ~RestClient();



private:
    struct Data;
    std::unique_ptr< Data > m_data;
};


}
