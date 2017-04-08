
#include "ConsoleWidget.h"

//Taken from Qt example

namespace Quartz { namespace Plugin { namespace SerialConsole {

struct ConsoleWidget::Data
{
    explicit Data( QWidget */*parent*/ )
    {

    }
};


ConsoleWidget::ConsoleWidget( QWidget *parent )
    : QPlainTextEdit{ parent }
    , m_data{ new Data{ this }}
{
    document()->setMaximumBlockCount(100);
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    setPalette(p);
}

ConsoleWidget::~ConsoleWidget()
{

}

void ConsoleWidget::keyPressEvent( QKeyEvent *evt )
{
    switch (evt->key()) {
    case Qt::Key_Backspace:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        break;
    default:
//        if ( localEchoEnabled )
        QPlainTextEdit::keyPressEvent(evt);
        emit getData(evt->text().toLocal8Bit());
    }
}

void ConsoleWidget::mousePressEvent( QMouseEvent */*evt*/ )
{
    setFocus();
}

void ConsoleWidget::mouseDoubleClickEvent( QMouseEvent */*evt*/ )
{

}

void ConsoleWidget::contextMenuEvent( QContextMenuEvent */*evt*/ )
{

}

} } }
