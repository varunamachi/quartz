
#include "SerialUtils.h"

namespace Quartz { namespace Plugin { namespace SerialConsole {

QString SerialUtils::decodeParity( QSerialPort::Parity parity )
{
    switch( parity ) {
        case QSerialPort::NoParity:     return "No Parity";
        case QSerialPort::EvenParity:   return "Even";
        case QSerialPort::OddParity:    return "Odd";
        case QSerialPort::MarkParity:   return "Mark";
        case QSerialPort::SpaceParity:  return "Space";
        case QSerialPort::UnknownParity:  return "Unknown";
    }
    return "Unknown";
}

QString SerialUtils::decodeStopBits(QSerialPort::StopBits stopBits)
{
    switch( stopBits ) {
    case QSerialPort::OneStop:         return "One" ;
    case QSerialPort::OneAndHalfStop:  return "One And Half";
    case QSerialPort::TwoStop:         return "Two";
    case QSerialPort::UnknownStopBits: return "Unknown";
    }
    return "Unknown";
}

QString SerialUtils::decodeFlowControl(QSerialPort::FlowControl flowControl)
{
    switch( flowControl ) {
        case QSerialPort::NoFlowControl:      return "No Flow Control";
        case QSerialPort::HardwareControl:    return "Hardware";
        case QSerialPort::SoftwareControl:    return "Software";
        case QSerialPort::UnknownFlowControl: return "Unknown";
    }
    return "Unknown";
}

} } }
