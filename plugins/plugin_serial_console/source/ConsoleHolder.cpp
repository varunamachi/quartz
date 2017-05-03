
#include <QToolBar>
#include <QAction>
#include <QSerialPort>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QSerialPortInfo>
#include <QTextStream>
#include <QComboBox>
#include <QLineEdit>
#include <QIntValidator>
#include <QVariant>
#include <QVariant>

#include <plugin_base/BundleLoggin.h>
#include <plugin_base/BundleContext.h>
#include <core/app_config/ConfigManager.h>

#include "SerialSettings.h"
#include "SettingsDialog.h"
#include "ConsoleWidget.h"
#include "ConsoleHolder.h"
#include "SerialUtils.h"
#include "Constants.h"

namespace Quartz { namespace Plugin { namespace SerialConsole {

struct ConsoleHolder::Data
{
    explicit Data( std::unique_ptr< SerialSettings > settings,
                   QWidget *parent )
        : m_settings{ std::move( settings )}
        , m_toolBar{ new QToolBar{ parent }}
        , m_connect{ new QAction{ QObject::tr( "Connect" ), parent }}
        , m_disconnect{ new QAction{ QObject::tr( "Disconnect" ), parent }}
        , m_clearConsole{ new QAction{ QObject::tr( "Clear" ), parent }}
        , m_console{ new ConsoleWidget{ parent }}
        , m_baudCombo{ new QComboBox{ parent }}
        , m_serial{ new QSerialPort{ parent }}
        , m_intValidator{ new QIntValidator{ 0, 40000000, parent }}
    {

//        m_baudCombo->addItem( QStringLiteral( "9600" ),
//                              QSerialPort::Baud9600 );
//        m_baudCombo->addItem( QStringLiteral( "19200" ),
//                              QSerialPort::Baud19200 );
//        m_baudCombo->addItem( QStringLiteral( "38400" ),
//                              QSerialPort::Baud38400 );
//        m_baudCombo->addItem( QStringLiteral( "115200" ),
//                              QSerialPort::Baud115200 );
        m_baudCombo->addItems( SerialUtils::allBaudRates() );
        m_baudCombo->setCurrentIndex( 1 );

        m_toolBar->addAction( m_connect );
        m_toolBar->addAction( m_disconnect );
        m_toolBar->addAction( m_clearConsole );
        m_toolBar->addWidget( m_baudCombo );

        updateDisplayName();
        updateCompleteInfo();
    }

    void setEnabled( bool value )
    {
        m_connect->setEnabled( value );
        m_disconnect->setEnabled( value );
        m_console->setEnabled( value );
        m_baudCombo->setEnabled( value );
    }

    void updateDisplayName()
    {
        QTextStream dpnStream{ &m_displayName };
        dpnStream << m_settings->name();
        if( ! m_settings->info().description().isEmpty() ) {
            dpnStream << " : " << m_settings->info().description();
        }
        dpnStream.flush();
    }

    void updateCompleteInfo()
    {
        const QString I = "    ";
        QTextStream infoStream{ &m_completeInfo };
        const auto &info = m_settings->info();
        infoStream << "<b>Information:</b><br>"
                   << I << tr( "Port Name" ) << ": <b>"
                   << info.portName() << "</b><br>"
                   << I << tr( "Description" ) << ": <b>"
                   << info.description() << "</b><br>"
                   << I << tr( "Serial Number" ) << ": <b>"
                   << info.serialNumber() << "</b><br>"
                   << I << tr( "Location" ) << ": <b>"
                   << info.systemLocation() << "</b><br>"
                   << I << tr( "VID" ) << ": <b>"
                   << int( info.vendorIdentifier() ) << "</b><br>"
                   << I << tr( "PID" ) << ": <b>"
                   << int( info.productIdentifier() ) << "</b><br>"
                   << "<br><b>Settings:</b><br>"
                   << I << tr( "Baud Rate" ) << ": <b>"
                   << m_settings->baudRate() << "</b><br>"
                   << I << tr( "Data Bits" ) << ": <b>"
                   << m_settings->dataBits() << "</b><br>"
                   << I << tr( "Parity" ) << ": <b>"
                   << SerialUtils::decodeParity( m_settings->parity() )
                   << "</b><br>"
                   << I << tr( "Stop Bits" ) << ": <b>"
                   << SerialUtils::decodeStopBits( m_settings->stopBits() )
                   << "</b><br>"
                   << I << tr( "Flow Control" ) << ": <b>"
                   << SerialUtils::decodeFlowControl( m_settings->flowControl())
                   << "</b><br>";
        infoStream.flush();
    }

    std::unique_ptr< SerialSettings > m_settings;

    QToolBar *m_toolBar;

    QAction *m_connect;

    QAction *m_disconnect;

    QAction *m_clearConsole;

    ConsoleWidget *m_console;

    QComboBox *m_baudCombo;

    QSerialPort *m_serial;

    QIntValidator *m_intValidator;

    QString m_displayName;

    QString m_completeInfo;


};

using SerialErrorFunc =
    void ( QSerialPort::* )( QSerialPort::SerialPortError );

ConsoleHolder::ConsoleHolder( std::unique_ptr< SerialSettings > settings,
                              QWidget *parent )
    : QWidget{ parent }
    , m_data{ new Data{ std::move( settings ), this }}
{
    auto layout = new QVBoxLayout{};
    layout->addWidget( m_data->m_toolBar );
    layout->addWidget( m_data->m_console );
    this->setLayout( layout );

    auto errorFunc = [ this ]( QSerialPort::SerialPortError err ) {
        if( err == QSerialPort::ResourceError ) {
            QMessageBox::critical(
                        this,
                        tr(" Serial Port Error"),
                        m_data->m_serial->errorString() );
            this->disconnect();
        }
        if( err != QSerialPort::NoError ) {
            QZP_ERROR << "Serial port error occured. Code: " << err
                      <<". " << m_data->m_serial->errorString();
        }
    };
    connect( m_data->m_serial,
             static_cast< SerialErrorFunc >( &QSerialPort::error ),
             errorFunc );
    connect( m_data->m_connect,
             &QAction::triggered,
             this,
             &ConsoleHolder::connectSerial );
    connect( m_data->m_disconnect,
             &QAction::triggered,
             this,
             &ConsoleHolder::disconnectSerial );
    connect( m_data->m_clearConsole,
             &QAction::triggered,
             m_data->m_console,
             &ConsoleWidget::clearConsole );
    connect( m_data->m_serial,
             &QSerialPort::readyRead,
             [ this ]() {
        auto data = m_data->m_serial->readAll();
        m_data->m_console->putData( data );
    });
    connect( m_data->m_console,
             &ConsoleWidget::sigDataEntered,
             [ this ]( const QByteArray &data ) {
        m_data->m_serial->write( data );
    });
    using ComboIdxFunc = void ( QComboBox::* )( int );
    connect( m_data->m_baudCombo,
             static_cast< ComboIdxFunc >( &QComboBox::currentIndexChanged ),
             [ this ]( int /*index*/ ) {

        auto txt = m_data->m_baudCombo->currentText();
        auto baud = static_cast< qint32 >( txt.toLong() );
        if( ! m_data->m_serial->setBaudRate( baud )) {
            m_data->m_baudCombo->setCurrentIndex( 1 );
        }
    });
    m_data->setEnabled( false );
}

ConsoleHolder::~ConsoleHolder()
{

}

const QString ConsoleHolder::displayName() const
{
    return m_data->m_displayName;
}

const QString ConsoleHolder::description() const
{
    return m_data->m_completeInfo;
}



bool ConsoleHolder::connectSerial()
{
    bool result = false;
    m_data->m_serial->setPortName( m_data->m_settings->name() );
    m_data->m_serial->setBaudRate( m_data->m_settings->baudRate() );
    m_data->m_serial->setDataBits( m_data->m_settings->dataBits() );
    m_data->m_serial->setParity( m_data->m_settings->parity() );
    m_data->m_serial->setStopBits( m_data->m_settings->stopBits() );
    m_data->m_serial->setFlowControl( m_data->m_settings->flowControl() );
    if( ! m_data->m_serial->open( QIODevice::ReadWrite )) {
        QZP_ERROR << "Failed to open serial port " << m_data->m_settings->name()
                  << ": " << m_data->m_serial->errorString();
        m_data->setEnabled( m_data->m_serial->isOpen() );
        QMessageBox::critical( this,
                               tr(" Serial Port Error"),
                               m_data->m_serial->errorString() );
    }
    else {
        m_data->setEnabled( true );
        result = true;
    }
    return result;
}

bool ConsoleHolder::disconnectSerial()
{
    m_data->m_serial->close();
    bool result = ! m_data->m_serial->isOpen();
    if( result ) {
        m_data->setEnabled( false );

        emit serialDisconnected( this );
    }
    return result;
}

void ConsoleHolder::clearConsole()
{
    m_data->m_console->clear();
}

void ConsoleHolder::updateBaudRates()
{
    m_data->m_baudCombo->clear();
    auto curRate = m_data->m_baudCombo->currentText();
    auto newCurIndex = -1;
    auto baudRates = SerialUtils::allBaudRates();
    for( auto i = 0; i < baudRates.size(); ++ i ) {
        const auto &rate = baudRates.at( i );
        if( rate == curRate ) {
            newCurIndex = i;
        }
        m_data->m_baudCombo->addItem( rate );
    }
    if( newCurIndex == -1 && ! curRate.isEmpty() ) {
        m_data->m_baudCombo->insertItem( 0, curRate );
        m_data->m_baudCombo->setCurrentIndex( 0 );
    }
    else {
        m_data->m_baudCombo->setCurrentIndex( newCurIndex );
    }
}

} } }
