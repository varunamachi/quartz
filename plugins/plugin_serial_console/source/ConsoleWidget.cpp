
#include <QTextBlock>

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
    p.setColor( QPalette::Base, Qt::black );
    p.setColor( QPalette::Text, Qt::green );
    setPalette(p);
    printPrompt();
#ifdef Q_OS_WIN
    this->setFont( QFont{ "Consolas", 12 });
#else
    this->setFont( QFont{ "Monospace", 12 });
#endif

}

ConsoleWidget::~ConsoleWidget()
{

}

void ConsoleWidget::putData( const QByteArray &data )
{
    this->appendPlainText( QString{ data });
    printPrompt();
}

QString ConsoleWidget::currentLineText()
{
    auto doc = this->document();
    int curLine = doc->lineCount() - 1;
    auto block = doc->findBlockByLineNumber( curLine );
    return block.text();
}

void ConsoleWidget::clearConsole()
{
    clear();
    printPrompt();
}

void ConsoleWidget::keyPressEvent( QKeyEvent *evt )
{
    switch (evt->key()) {

    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        break;
    case Qt::Key_Backspace: {
        auto curLine = currentLineText();
        if( ! ( curLine.size() == 3 && curLine == ">> " )) {
            QPlainTextEdit::keyPressEvent( evt );
        }
    }
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter: {
        if( evt->modifiers() && Qt::ControlModifier ) {
            emit sigDataEntered( this->toPlainText().toLocal8Bit() );
            printPrompt();
        }
        else {
            QPlainTextEdit::keyPressEvent( evt );
        }
    }
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

void ConsoleWidget::printPrompt()
{
    this->appendHtml(
                QString{ "<font color = 'red'><bold>\n>></bold></font> " });
}

} } }
