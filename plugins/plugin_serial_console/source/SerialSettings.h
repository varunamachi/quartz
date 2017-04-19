#pragma once

#include <memory>

#include <QSerialPort>

namespace Quartz { namespace Plugin { namespace SerialConsole {

class SerialSettings
{
public:
    SerialSettings( const QString &name,
                    const qint32 baudRate,
                    const QSerialPort::DataBits dataBits,
                    const QSerialPort::Parity parity,
                    const QSerialPort::StopBits stopBits,
                    const QSerialPort::FlowControl flowControl,
                    const QSerialPortInfo &info );

    ~SerialSettings();

    const QString & name() const;

    qint32 baudRate() const;

    QSerialPort::DataBits dataBits() const;

    QSerialPort::Parity parity() const;

    QSerialPort::StopBits stopBits() const;

    QSerialPort::FlowControl flowControl() const;

    const QSerialPortInfo & info() const;

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

} } }
