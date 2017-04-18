
#include <QToolBar>
#include <QAction>
#include <QSerialPort>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

#include <plugin_base/BundleLoggin.h>

#include "SerialSettings.h"
#include "SettingsDialog.h"
#include "ConsoleWidget.h"
#include "ConsoleHolder.h"

namespace Quartz { namespace Plugin { namespace SerialConsole {

struct ConsoleHolder::Data
{
    explicit Data( std::unique_ptr< SerialSettings > settings,
                   QWidget *parent )
        : m_toolBar{ new QToolBar{ parent }}
        , m_settings{ std::move( settings )}

        , m_connect{ new QAction{ QObject::tr( "Connect" ), parent }}
        , m_disconnect{ new QAction{ QObject::tr( "Disconnect" ), parent }}
        , m_clearConsole{ new QAction{ QObject::tr( "Clear" ), parent }}
        , m_console{ new ConsoleWidget{ parent }}

        , m_serial{ new QSerialPort{ parent }}
    {
        m_toolBar->addAction( m_connect );
        m_toolBar->addAction( m_disconnect );
        m_toolBar->addAction( m_clearConsole );
    }

    void setEnabled( bool value )
    {
        m_connect->setEnabled( value );
        m_disconnect->setEnabled( value );
        m_console->setEnabled( value );
    }

    QToolBar *m_toolBar;

    QAction *m_connect;

    QAction *m_disconnect;

    QAction *m_clearConsole;

    ConsoleWidget *m_console;

    QSerialPort *m_serial;

    std::unique_ptr< SerialSettings > m_settings;


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

    m_data->setEnabled( false );
}

ConsoleHolder::~ConsoleHolder()
{

}

const QString &ConsoleHolder::name() const
{
    return m_data->m_settings->name();
}

void ConsoleHolder::connectSerial()
{
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
    }
}

void ConsoleHolder::disconnectSerial()
{
    m_data->m_serial->close();
    m_data->setEnabled( m_data->m_serial->isOpen() );
}

void ConsoleHolder::clearConsole()
{
    m_data->m_console->clear();
}


} } }
