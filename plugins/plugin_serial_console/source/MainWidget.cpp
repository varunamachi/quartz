
#include <QVBoxLayout>
#include <QLabel>

#include "ConsoleWidget.h"
#include "MainWidget.h"



namespace Quartz { namespace Plugin { namespace  SerialConsole {

const QString MainWidget::CONTENT_ID{ "qzp.serial_console.content.main" };
const QString MainWidget::CONTENT_NAME{ "SerialConsoleMain" };
const QString MainWidget::CONTENT_KIND{ "hw" };

struct MainWidget::Data
{
    Data( QWidget *parent )
        : m_console{ new ConsoleWidget{ parent }}
    {

    }

    ConsoleWidget *m_console;
};

MainWidget::MainWidget( QWidget *parent )
    : ContentWidget{ CONTENT_ID, CONTENT_NAME, CONTENT_KIND, parent }
    , m_data{ new Data{ this }}
{
    auto layout = new QVBoxLayout{};
    layout->addWidget( new QLabel{ tr( "Serial Consle PH" )});
    layout->addWidget( m_data->m_console );
    this->setLayout( layout );

    this->setContentsMargins( QMargins{} );
    layout->setContentsMargins( QMargins{} );
}

MainWidget::~MainWidget()
{

}

} } }
