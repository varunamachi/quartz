#pragma once

#include <QSerialPort>

#include <core/utils/Macros.h>


namespace Quartz { namespace Plugin { namespace SerialConsole {

class SerialUtils
{
public:
    QZ_MAKE_STATIC( SerialUtils );

    static QString decodeParity( QSerialPort::Parity parity );

    static QString decodeStopBits( QSerialPort::StopBits stopBits );

    static QString decodeFlowControl( QSerialPort::FlowControl flowControl );

private:
};

} } }
