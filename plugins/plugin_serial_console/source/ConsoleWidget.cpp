
#include "ConsoleWidget.h"

namespace Quartz { namespace Plugin { namespace SerialConsole {

struct ConsoleWidget::Data
{
    explicit Data( QWidget */*parent*/ )
    {

    }
};


ConsoleWidget::ConsoleWidget( QWidget *parent )
    : QTextEdit{ parent }
    , m_data{ new Data{ this }}
{

}

ConsoleWidget::~ConsoleWidget()
{

}


} } }
