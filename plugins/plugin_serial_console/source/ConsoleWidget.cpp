
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

void ConsoleWidget::putData( const QByteArray &data )
{
    this->appendPlainText( "\n" + QString{ data });
    this->appendPlainText( QString{ "\n>> " });
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
    case Qt::Key_Enter:
        emit sigDataEntered( this->toPlainText().toLocal8Bit() );
        QPlainTextEdit::keyPressEvent( evt );
        this->appendPlainText( QString{ "\n>> " });
        break;
    default:
        QPlainTextEdit::keyPressEvent( evt );
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
