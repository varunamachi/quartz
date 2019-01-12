#pragma once

#include <memory>

#include <QWidget>

namespace Quartz { namespace Ext { namespace SerialConsole {

class SerialSettings;

class ConsoleHolder : public QWidget
{
    Q_OBJECT
public:
    explicit ConsoleHolder(std::unique_ptr<SerialSettings> settings,
                            QWidget *parent = nullptr);

    ~ConsoleHolder();

    const QString displayName() const;

    const QString description() const;

    bool isConnected() const;

public slots:
    bool connectSerial();

    bool disconnectSerial();

    void clearConsole();

    void updateBaudRates();

private slots:
    void setBaudRate(int index);

signals:
    void serialDisconnected(ConsoleHolder *holder);

private:
    struct Data;
    std::unique_ptr<Data> m_data;

};

} } }
