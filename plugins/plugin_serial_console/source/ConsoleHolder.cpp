
#include <QToolBar>
#include <QAction>
#include <QSerialPort>

#include "SerialSettings.h"
#include "SettingsDialog.h"
#include "ConsoleHolder.h"

namespace Quartz { namespace Plugin { namespace SerialConsole {

struct ConsoleHolder::Data
{
    explicit Data( QWidget *parent )
        : m_toolBar{ new QToolBar{ parent }}
        , m_configure{ new QAction{ QObject::tr( "Configure" ), parent }}
        , m_connect{ new QAction{ QObject::tr( "Connect" ), parent }}
        , m_disconnect{ new QAction{ QObject::tr( "Disconnect" ), parent }}
        , m_dialog{ new SettingsDialog{ parent }}
        , m_serial{ nullptr }
        , m_settings{ nullptr }
    {

    }

    QToolBar *m_toolBar;

    QAction *m_configure;

    QAction *m_connect;

    QAction *m_disconnect;

    SettingsDialog *m_dialog;

    QSerialPort *m_serial;

    std::unique_ptr< SerialSettings > m_settings;


};

ConsoleHolder::ConsoleHolder( QWidget *parent )
    : QWidget{ parent }
    , m_data{ new Data{ this }}
{

}

ConsoleHolder::~ConsoleHolder()
{

}

void ConsoleHolder::onConfigure()
{

}

void ConsoleHolder::onConnect()
{

}

void ConsoleHolder::onDisconnect()
{

}



} } }
