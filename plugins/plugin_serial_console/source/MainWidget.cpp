
#include <QVBoxLayout>
#include <QLabel>
#include <QSerialPort>
//#include <QTabBar>

#include "ConsoleHolder.h"
#include "MainWidget.h"



namespace Quartz { namespace Plugin { namespace  SerialConsole {

const QString MainWidget::CONTENT_ID{ "qzp.serial_console.content.main" };
const QString MainWidget::CONTENT_NAME{ "SerialConsoleMain" };
const QString MainWidget::CONTENT_KIND{ "hw" };

struct MainWidget::Data
{
    Data( QWidget *parent )
        : m_holder{ new ConsoleHolder{ parent }}
    {

    }

    ConsoleHolder *m_holder;

};

MainWidget::MainWidget( QWidget *parent )
    : ContentWidget{ CONTENT_ID, CONTENT_NAME, CONTENT_KIND, parent }
    , m_data{ new Data{ this }}
{
    auto layout = new QVBoxLayout{};
    layout->addWidget( m_data->m_holder );
    this->setLayout( layout );

    this->setContentsMargins( QMargins{} );
    layout->setContentsMargins( QMargins{} );
}

MainWidget::~MainWidget()
{

}

} } }
