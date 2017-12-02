
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
#include <QSplitter>
#include <QScrollBar>

#include <core/app_config/ConfigManager.h>
#include <core/utils/ScopedOperation.h>

#include <plugin_base/PluginLogging.h>
#include <plugin_base/PluginContext.h>

#include "SerialSettings.h"
#include "SettingsDialog.h"
#include "ConsoleWidget.h"
#include "ConsoleHolder.h"
#include "SerialUtils.h"
#include "Constants.h"

namespace Quartz { namespace Ext { namespace SerialConsole {

using SerialErrorFunc =
    void ( QSerialPort::* )( QSerialPort::SerialPortError );

using ComboIdxFunc = void ( QComboBox::* )( int );

struct ConsoleHolder::Data
{
    explicit Data( std::unique_ptr< SerialSettings > settings,
                   QWidget *parent );

    void setEnabled( bool value );

    void updateDisplayName();

    void updateCompleteInfo();

    void setBaudRate( int index );

    std::unique_ptr< SerialSettings > m_settings;

    QToolBar *m_toolBar;

    QAction *m_connect;

    QAction *m_disconnect;

    QAction *m_clearConsole;

    ConsoleWidget *m_console;

    QPlainTextEdit *m_outConsole;

    QComboBox *m_baudCombo;

    QSerialPort *m_serial;

    QIntValidator *m_intValidator;

    QString m_displayName;

    QString m_completeInfo;


};

ConsoleHolder::Data::Data( std::unique_ptr< SerialSettings > settings,
                           QWidget *parent )
    : m_settings{ std::move( settings )}
    , m_toolBar{ new QToolBar{ parent }}
    , m_connect{ new QAction{ QObject::tr( "Connect" ), parent }}
    , m_disconnect{ new QAction{ QObject::tr( "Disconnect" ), parent }}
    , m_clearConsole{ new QAction{ QObject::tr( "Clear" ), parent }}
    , m_console{ new ConsoleWidget{ parent }}
    , m_outConsole{ new QPlainTextEdit{ parent }}
    , m_baudCombo{ new QComboBox{ parent }}
    , m_serial{ new QSerialPort{ parent }}
    , m_intValidator{ new QIntValidator{ 0, 40000000, parent }}
{
    m_baudCombo->addItems( SerialUtils::allBaudRates() );
    auto curBaudText = QString::number( m_settings->baudRate() );
    m_baudCombo->setCurrentText( curBaudText );

    m_toolBar->addAction( m_connect );
    m_toolBar->addAction( m_disconnect );
    m_toolBar->addAction( m_clearConsole );
    m_toolBar->addWidget( m_baudCombo );

    QPalette p = m_outConsole->palette();
    p.setColor( QPalette::Base, Qt::black );
    p.setColor( QPalette::Text, Qt::green );
    m_outConsole->setPalette( p );
    m_outConsole->setReadOnly( true );
#ifdef Q_OS_WIN
    m_outConsole->setFont( QFont{ "Consolas", 12 });
#else
    m_outConsole->setFont( QFont{ "Monospace", 12 });
#endif

    updateDisplayName();
    updateCompleteInfo();
}

void ConsoleHolder::Data::setEnabled( bool value )
{
    m_connect->setEnabled( value );
    m_disconnect->setEnabled( value );
    m_console->setEnabled( value );
    m_baudCombo->setEnabled( value );
}

void ConsoleHolder::Data::updateDisplayName()
{
    QTextStream dpnStream{ &m_displayName };
    dpnStream << m_settings->name();
    if( ! m_settings->info().description().isEmpty() ) {
        dpnStream << " : " << m_settings->info().description();
    }
    dpnStream.flush();
}

void ConsoleHolder::Data::updateCompleteInfo()
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




//-----------------------real ConsoleHolder----------------------------------


ConsoleHolder::ConsoleHolder( std::unique_ptr< SerialSettings > settings,
                              QWidget *parent )
    : QWidget{ parent }
    , m_data{ new Data{ std::move( settings ), this }}
{
    auto layout = new QVBoxLayout{};
    layout->addWidget( m_data->m_toolBar );

    auto splitter = new QSplitter{ Qt::Horizontal, this };
    splitter->addWidget( m_data->m_console );
    splitter->addWidget( m_data->m_outConsole );
    layout->addWidget( splitter );
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
    connect( m_data->m_baudCombo,
             static_cast< ComboIdxFunc >( &QComboBox::currentIndexChanged ),
             this,
             &ConsoleHolder::setBaudRate );
    connect( m_data->m_serial,
             &QSerialPort::readyRead,
             [ this ]() {
        auto data = m_data->m_serial->readAll();
        m_data->m_outConsole->insertPlainText( QString{ data });
        m_data->m_outConsole->verticalScrollBar()->setValue(
                    m_data->m_outConsole->verticalScrollBar()->maximum());
    });
    connect( m_data->m_console,
             &ConsoleWidget::sigDataEntered,
             [ this ]( const QByteArray &data ) {
        auto html = "<br>Command: <font color=red><b>"
                    + QString{ data }
                    + "</b></font><br>"
                    + "---------------------------------------------------<br>";
        m_data->m_serial->write( data );
        m_data->m_outConsole->textCursor().insertHtml( html );
        m_data->m_outConsole->verticalScrollBar()->setValue(
                    m_data->m_outConsole->verticalScrollBar()->maximum());
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
        QZP_INFO << "Connecteed to " << m_data->m_serial->portName()
                 << " successfully";
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
        QZP_INFO << "Disconnected " << m_data->m_serial->portName()
                 << " successfully";
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
    auto curRate = m_data->m_baudCombo->currentText();
    auto newCurIndex = -1;
    m_data->m_baudCombo->clear();
    auto baudRates = SerialUtils::allBaudRates();
    for( auto i = 0; i < baudRates.size(); ++ i ) {
        const auto &rate = baudRates.at( i );
        if( rate == curRate ) {
            newCurIndex = i;
        }
//        m_data->m_baudCombo->blockSignals( true );
        m_data->m_baudCombo->addItem( rate );
//        m_data->m_baudCombo->blockSignals( false );
    }
    if( newCurIndex == -1 || curRate.isEmpty() ) {
        m_data->m_baudCombo->setCurrentIndex( 0 );
    }
    else if( ! curRate.isEmpty() ){
        m_data->m_baudCombo->setCurrentIndex( newCurIndex );
    }
}

void ConsoleHolder::setBaudRate( int index )
{
    if( index != -1 ) {
        auto txt = m_data->m_baudCombo->currentText();
        auto baud = static_cast< qint32 >( txt.toLong() );
        if( baud == m_data->m_serial->baudRate() ) {
            return;
        }
        if( ! m_data->m_serial->setBaudRate( baud )) {
            SCOPE_LIMIT( m_data->m_baudCombo->blockSignals( true ),
                         m_data->m_baudCombo->blockSignals( false ));
            auto oldRate = m_data->m_serial->baudRate();
            auto rateStr = QString::number( oldRate );
            m_data->m_baudCombo->setCurrentText( rateStr );
            QZP_ERROR << "Failed to set baud rate of " << baud << " to "
                      << m_data->m_serial->portName() << ". Reverting to "
                      << oldRate;
        }
        else {
            QZP_INFO << "Baud rate of " << m_data->m_serial->portName()
                     << " set to " << baud;
        }
    }
}

} } }
