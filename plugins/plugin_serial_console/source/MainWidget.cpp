
#include <QVBoxLayout>
#include <QLabel>
#include <QSerialPort>
#include <QTabBar>
#include <QToolBar>
#include <QStackedWidget>

#include "ConsoleHolder.h"
#include "MainWidget.h"
#include "SettingsDialog.h"
#include "SerialSettings.h"


namespace Quartz { namespace Plugin { namespace  SerialConsole {

const QString MainWidget::CONTENT_ID{ "qzp.serial_console.content.main" };
const QString MainWidget::CONTENT_NAME{ "SerialConsoleMain" };
const QString MainWidget::CONTENT_KIND{ "hw" };

struct MainWidget::Data
{
    Data( QWidget *parent )
        : m_toolBar{ new QToolBar{ parent }}
        , m_tabBar{ new QTabBar{ parent }}
        , m_stackedWidget{ new QStackedWidget{ parent }}
        , m_newConnection{ new QAction{ QObject::tr( "New Connection" ),
                           parent }}
        , m_disconnectAll{ new QAction{ QObject::tr( "Disconnect All" ),
                           parent }}
        , m_dialog{ new SettingsDialog{ parent }}
    {
        m_toolBar->addAction( m_newConnection );
        m_toolBar->addAction( m_disconnectAll );
    }

    QToolBar *m_toolBar;

    QTabBar *m_tabBar;

    QStackedWidget *m_stackedWidget;

    QAction *m_newConnection;

    QAction *m_disconnectAll;

    SettingsDialog *m_dialog;
};

MainWidget::MainWidget( QWidget *parent )
    : ContentWidget{ CONTENT_ID, CONTENT_NAME, CONTENT_KIND, parent }
    , m_data{ new Data{ this }}
{
    auto layout = new QVBoxLayout{};
    layout->addWidget( m_data->m_toolBar );
    layout->addWidget( m_data->m_tabBar );
    layout->addWidget( m_data->m_stackedWidget );
    this->setLayout( layout );

    this->setContentsMargins( QMargins{} );
    layout->setContentsMargins( QMargins{} );

    connect( m_data->m_newConnection,
             &QAction::triggered,
             [ this ]() {
        m_data->m_dialog->refresh();
        m_data->m_dialog->open();
    });
    connect( m_data->m_dialog,
             &QDialog::accepted,
             [ this ]() {
//        m_data->m_settings = m_data->m_dialog->settings();
//        onConnect();
        auto holder = new ConsoleHolder{ m_data->m_dialog->settings(), this };
        holder->connectSerial();
        m_data->m_tabBar->addTab( holder->name() );
        m_data->m_stackedWidget->addWidget( holder );
    });

}

MainWidget::~MainWidget()
{

}

} } }
