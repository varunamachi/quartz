
#include <QVBoxLayout>
#include <QLabel>
#include <QSerialPort>
#include <QToolBar>
#include <QTabWidget>
//#include <QTabBar>
//#include <QStackedWidget>

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
        , m_tabWidget{ new QTabWidget{ parent }}
        , m_newConnection{ new QAction{ QObject::tr( "New Connection" ),
                           parent }}
        , m_disconnectAll{ new QAction{ QObject::tr( "Disconnect All" ),
                           parent }}
        , m_dialog{ new SettingsDialog{ parent }}
    {
        m_toolBar->addAction( m_newConnection );
        m_toolBar->addAction( m_disconnectAll );
        m_tabWidget->setTabsClosable( true );
    }

    QToolBar *m_toolBar;

    QTabWidget *m_tabWidget;

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
    layout->addWidget( m_data->m_tabWidget );
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
             this,
             &MainWidget::createNewConnection );
    connect( m_data->m_tabWidget,
             &QTabWidget::tabBarDoubleClicked,
             [ this ]( int index ) {
        if( index == -1 ) {
            m_data->m_dialog->refresh();
            m_data->m_dialog->open();
        }
    });
    connect( m_data->m_tabWidget,
             &QTabWidget::tabCloseRequested,
             [ this ]( int index ) {
        auto widget = m_data->m_tabWidget->widget( index );
        auto holder = qobject_cast< ConsoleHolder *>( widget );
        if( holder != nullptr ) {
            holder->disconnectSerial();
        }
    });

    layout->setContentsMargins( QMargins{} );
    m_data->m_toolBar->setContentsMargins( 0, 0, 0, 4 );
    m_data->m_tabWidget->setContentsMargins( 0, 0, 0, 4 );
}

MainWidget::~MainWidget()
{

}

void MainWidget::createNewConnection()
{
    auto holder = new ConsoleHolder{ m_data->m_dialog->settings(), this };
    if( holder->connectSerial() ) {
        auto index = m_data->m_tabWidget->addTab( holder,
                                                  holder->displayName() );
        m_data->m_tabWidget->setTabToolTip( index, holder->description() );
        connect( holder,
                 &ConsoleHolder::serialDisconnected,
                 [ this ]( ConsoleHolder *obj ) {
            auto index = m_data->m_tabWidget->indexOf( obj );
            m_data->m_tabWidget->removeTab( index );
        });
    }
    else {
        delete holder;
    }
}

} } }
