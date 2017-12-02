#pragma once

#include <QSerialPort>

#include <core/utils/Macros.h>


namespace Quartz { namespace Ext { namespace SerialConsole {

class SerialUtils
{
public:
    QZ_MAKE_STATIC( SerialUtils );

    static QString decodeParity( QSerialPort::Parity parity );

    static QString decodeStopBits( QSerialPort::StopBits stopBits );

    static QString decodeFlowControl( QSerialPort::FlowControl flowControl );

    static QStringList standardBaudRates();

    static QStringList customBaudRates();

    static QStringList allBaudRates();

    static void storeBaudRates( const QStringList &rates );

private:
};

} } }
