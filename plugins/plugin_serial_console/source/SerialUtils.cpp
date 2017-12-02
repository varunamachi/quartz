
#include <QVariant>

#include <core/app_config/ConfigManager.h>

#include <plugin_base/PluginContext.h>

#include "Constants.h"
#include "SerialUtils.h"

namespace Quartz { namespace Ext { namespace SerialConsole {

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

QStringList SerialUtils::standardBaudRates()
{
    QStringList stdRates;
    stdRates << QStringLiteral( "9600" )
             << QStringLiteral( "19200" )
             << QStringLiteral( "38400" )
             << QStringLiteral( "115200" );
    return stdRates;
}

QStringList SerialUtils::customBaudRates()
{
    auto var = confman()->retrieve( Constants::KEY_BAUD_RATES,
                                    Constants::CONFIG_DOMAIN );
    return var.toStringList();
}

QStringList SerialUtils::allBaudRates()
{
    auto rates = standardBaudRates();
    auto var = confman()->retrieve( Constants::KEY_BAUD_RATES,
                                    Constants::CONFIG_DOMAIN );
    QStringList nonStd = var.toStringList();
    rates.append( nonStd );
    return rates;
}

void SerialUtils::storeBaudRates( const QStringList &rates )
{
    auto stdRates = standardBaudRates();
    QStringList nonStandard;
    foreach( auto &rate, rates ) {
        if( ! stdRates.contains( rate )) {
            nonStandard << rate;
        }
    }
    confman()->store( Constants::KEY_BAUD_RATES,
                      nonStandard,
                      Constants::CONFIG_DOMAIN );
}

} } }
