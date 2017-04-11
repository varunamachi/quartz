
#include <QToolBar>
#include <QAction>
#include <QSerialPort>
#include <QVBoxLayout>
#include <QLabel>

#include "SerialSettings.h"
#include "SettingsDialog.h"
#include "ConsoleWidget.h"
#include "ConsoleHolder.h"

namespace Quartz { namespace Plugin { namespace SerialConsole {

struct ConsoleHolder::Data
{
    explicit Data( QWidget *parent )
        : m_toolBar{ new QToolBar{ parent }}
        , m_configure{ new QAction{ QObject::tr( "Configure" ), parent }}
        , m_connect{ new QAction{ QObject::tr( "Connect" ), parent }}
        , m_disconnect{ new QAction{ QObject::tr( "Disconnect" ), parent }}
        , m_clearConsole{ new QAction{ QObject::tr( "Clear" ), parent }}
        , m_console{ new ConsoleWidget{ parent }}
        , m_dialog{ new SettingsDialog{ parent }}
        , m_serial{ nullptr }
        , m_settings{ nullptr }
    {
        m_toolBar->addAction( m_configure );
        m_toolBar->addAction( m_connect );
        m_toolBar->addAction( m_disconnect );
        m_toolBar->addAction( m_clearConsole );
    }

    QToolBar *m_toolBar;

    QAction *m_configure;

    QAction *m_connect;

    QAction *m_disconnect;

    QAction *m_clearConsole;

    ConsoleWidget *m_console;

    SettingsDialog *m_dialog;

    QSerialPort *m_serial;

    std::unique_ptr< SerialSettings > m_settings;


};

ConsoleHolder::ConsoleHolder( QWidget *parent )
    : QWidget{ parent }
    , m_data{ new Data{ this }}
{
    auto layout = new QVBoxLayout{};
    layout->addWidget( m_data->m_toolBar );
    layout->addWidget( m_data->m_console );
    this->setLayout( layout );

    connect( m_data->m_configure,
             &QAction::triggered,
             this,
             &ConsoleHolder::onConfigure );
    connect( m_data->m_connect,
             &QAction::triggered,
             this,
             &ConsoleHolder::onConnect );
    connect( m_data->m_disconnect,
             &QAction::triggered,
             this,
             &ConsoleHolder::onDisconnect );
    connect( m_data->m_clearConsole,
             &QAction::triggered,
             this,
             &ConsoleHolder::onClearConsole );
}

ConsoleHolder::~ConsoleHolder()
{

}

void ConsoleHolder::onConfigure()
{
    m_data->m_dialog->refresh();
    m_data->m_dialog->open();
    m_data->m_settings = m_data->m_dialog->settings();
    onConnect();
}

void ConsoleHolder::onConnect()
{

}

void ConsoleHolder::onDisconnect()
{

}

void ConsoleHolder::onClearConsole()
{

}

void ConsoleHolder::onDataReceived( const QByteArray &/*data*/ )
{

}

void ConsoleHolder::onDataEntered( const QByteArray &/*data*/ )
{

}



} } }
