#pragma once

#include <memory>

#include <QWidget>

namespace Quartz { namespace Plugin { namespace SerialConsole {

class ConsoleHolder : public QWidget
{
    Q_OBJECT
public:
    explicit ConsoleHolder( QWidget *parent = nullptr );

    ~ConsoleHolder();

private slots:
    void onConfigure();

    void onConnect();

    void onDisconnect();

    void onClearConsole();

    void onDataReceived(const QByteArray &data );

    void onDataEntered( const QByteArray &data );

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

} } }
