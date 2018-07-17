
#include <QVBoxLayout>
#include <QLabel>
#include <QSerialPort>
#include <QToolBar>
#include <QTabWidget>

#include <common/iconstore/IconFontStore.h>

#include "ConsoleHolder.h"
#include "MainWidget.h"
#include "SettingsDialog.h"
#include "SerialSettings.h"
#include "Dialogs.h"
#include "BaudRateEditDialog.h"

namespace Quartz { namespace Ext { namespace  SerialConsole {

const QString MainWidget::CONTENT_ID{ "qzp.serial_console.content.main" };
const QString MainWidget::CONTENT_NAME{ "SerialConsoleMain" };
const QString MainWidget::CONTENT_KIND{ "hw" };

struct MainWidget::Data
{
    Data( QWidget *parent )
        : m_toolBar{ new QToolBar{ parent }}
        , m_tabWidget{ new QTabWidget{ parent }}
        , m_newConnection{new QAction(
                              getIcon(FAIcon::Plug),
                              QObject::tr("New Connection"),
                              parent )}
        , m_editBaudRates{new QAction(
                              getIcon(MatIcon::Edit),
                              QObject::tr( "Edit Baud Rates" ),
                              parent)}
        , m_disconnectAll{new QAction(
                              getIcon(MatIcon::Clear),
                              QObject::tr( "Disconnect All" ),
                              parent)}
    {
        m_toolBar->addAction( m_newConnection );
        m_toolBar->addAction( m_disconnectAll );
        m_toolBar->addAction( m_editBaudRates );
        m_toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        m_tabWidget->setTabsClosable( true );
    }

    QToolBar *m_toolBar;

    QTabWidget *m_tabWidget;

    QAction *m_newConnection;

    QAction *m_editBaudRates;

    QAction *m_disconnectAll;
};

MainWidget::MainWidget( QWidget *parent )
    : ContentWidget{ CONTENT_ID, CONTENT_NAME, CONTENT_KIND, parent }
    , m_data{ new Data{ this }}
{
    auto layout = new QVBoxLayout{};
    layout->addWidget( m_data->m_toolBar );
    layout->addWidget( m_data->m_tabWidget );
    this->setLayout( layout );

    layout->setContentsMargins({} );

    connect( m_data->m_newConnection,
             &QAction::triggered,
             this,
             &MainWidget::createNewConnection );
    connect( m_data->m_tabWidget,
             &QTabWidget::tabBarDoubleClicked,
             this,
             &MainWidget::createNewConnection );
    connect( m_data->m_editBaudRates,
             &QAction::triggered,
             [ & ]() {
        Dialogs::openBaudRateEditor();
    });
    connect( m_data->m_tabWidget,
             &QTabWidget::tabCloseRequested,
             [ this ]( int index ) {
        auto widget = m_data->m_tabWidget->widget( index );
        auto holder = qobject_cast< ConsoleHolder *>( widget );
        if (holder != nullptr && holder->isConnected()) {
            holder->disconnectSerial();
        }
        auto idx = m_data->m_tabWidget->indexOf( widget );
        m_data->m_tabWidget->removeTab( idx );
    });
    connect( m_data->m_disconnectAll,
             &QAction::triggered,
             this,
             &MainWidget::disconnectAll );

    this->setContentsMargins(5, 5, 5, 5);
//    layout->setContentsMargins( QMargins{} );
//    m_data->m_toolBar->setContentsMargins( 0, 0, 0, 4 );
//    m_data->m_tabWidget->setContentsMargins( 0, 0, 0, 4 );

    Dialogs::init( this );
}

MainWidget::~MainWidget()
{
    disconnectAll();
}

void MainWidget::createNewConnection()
{
    auto settings = Dialogs::openSettings();
    if( settings != nullptr ) {
        auto holder = new ConsoleHolder{ std::move( settings ), this };
        if( holder->connectSerial() ) {
            auto index = m_data->m_tabWidget->addTab( holder,
                                                      holder->displayName() );
            m_data->m_tabWidget->setTabToolTip( index, holder->description() );
            connect( holder,
                     &ConsoleHolder::serialDisconnected,
                     [ this ]( ConsoleHolder *obj ) {
                auto index = m_data->m_tabWidget->indexOf( obj );
//                m_data->m_tabWidget->removeTab( index );
                m_data->m_tabWidget->setTabText(index,
                                                tr("[DISCONNECTED]"));
            });
            connect( Dialogs::baudRateEditDialog(),
                     &BaudRateEditDialog::baudRateChanged,
                     holder,
                     &ConsoleHolder::updateBaudRates );
        }
        else {
            delete holder;
        }
    }
}

void MainWidget::disconnectAll()
{
    for( auto i = 0; i < m_data->m_tabWidget->count(); ++ i ) {
        auto item = m_data->m_tabWidget->widget( i );
        auto conHolder = qobject_cast< ConsoleHolder *>( item );
        if( conHolder != nullptr ) {
            conHolder->disconnectSerial();
        }
    }
}

} } }
