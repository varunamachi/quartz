#pragma once

#include <memory>

#include <QWidget>

namespace Quartz { namespace Plugin { namespace SerialConsole {

class SerialSettings;

class ConsoleHolder : public QWidget
{
    Q_OBJECT
public:
    explicit ConsoleHolder( std::unique_ptr< SerialSettings > settings,
                            QWidget *parent = nullptr );

    ~ConsoleHolder();

    const QString & name() const;

public slots:
    void connectSerial();

    void disconnectSerial();

    void clearConsole();

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

} } }
