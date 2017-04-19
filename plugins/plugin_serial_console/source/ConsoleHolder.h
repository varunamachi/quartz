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

    const QString displayName() const;

    const QString description() const;

public slots:
    bool connectSerial();

    bool disconnectSerial();

    void clearConsole();

signals:
    void serialDisconnected( ConsoleHolder *holder );

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

} } }
