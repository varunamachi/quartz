
#include <QString>
#include <QSerialPort>


#include "SerialSettings.h"


namespace Quartz { namespace Plugin { namespace SerialConsole {

struct SerialSettings::Data
{
    Data( const QString &name,
          const qint32 baudRate,
          const QSerialPort::DataBits dataBits,
          const QSerialPort::Parity parity,
          const QSerialPort::StopBits stopBits,
          const QSerialPort::FlowControl flowControl )
        : m_name{ name }
        , m_baudRate{ baudRate }
        , m_dataBits{ dataBits }
        , m_parity{ parity }
        , m_stopBits{ stopBits }
        , m_flowControl{ flowControl }
    {

    }

    QString m_name;

    qint32 m_baudRate;

    QSerialPort::DataBits m_dataBits;

    QSerialPort::Parity m_parity;

    QSerialPort::StopBits m_stopBits;

    QSerialPort::FlowControl m_flowControl;
};

SerialSettings::SerialSettings( const QString &name,
                                const qint32 baudRate,
                                const QSerialPort::DataBits dataBits,
                                const QSerialPort::Parity parity,
                                const QSerialPort::StopBits stopBits,
                                const QSerialPort::FlowControl flowControl)
    : m_data{ new Data{ name,
                        baudRate,
                        dataBits,
                        parity,
                        stopBits,
                        flowControl }}
{

}

SerialSettings::~SerialSettings()
{

}

const QString &SerialSettings::name() const
{
    return  m_data->m_name;
}

qint32 SerialSettings::baudRate() const
{
    return  m_data->m_baudRate;
}

QSerialPort::DataBits SerialSettings::dataBits() const
{
    return m_data->m_dataBits;
}

QSerialPort::Parity SerialSettings::parity() const
{
    return m_data->m_parity;
}

QSerialPort::StopBits SerialSettings::stopBits() const
{
    return m_data->m_stopBits;
}

QSerialPort::FlowControl SerialSettings::flowControl() const
{
    return m_data->m_flowControl;
}


} } }
