
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
//    this->appendPlainText( QString{ data });
    this->moveCursor( QTextCursor::End );
    this->insertPlainText( data );
    this->moveCursor( QTextCursor::End );
//    printPrompt();
}

QString ConsoleWidget::currentCommand()
{
    auto doc = this->document();
    int curLine = doc->lineCount() - 1;
    QString cmd = "";
    while( curLine >= 0 ) {
        auto block = doc->findBlockByLineNumber( curLine );
        auto txt = block.text();
        cmd = txt + cmd;
        if( txt.startsWith( ">> " ) || txt.isEmpty() ) {
            break;
        }
        -- curLine;
    }
    cmd = cmd.trimmed();
    if( ! cmd.isEmpty() ) {
        return cmd.mid( 3 ) + "\r\n";
    }
    return cmd;
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
    case Qt::Key_Home: {
        this->moveCursor( QTextCursor::StartOfLine );
        auto cursor = this->textCursor();
        cursor.movePosition( QTextCursor::NextCharacter,
                             QTextCursor::MoveAnchor,
                             3 );
        this->setTextCursor( cursor );
    }
        break;
    case Qt::Key_Backspace: {
        auto curLine = currentCommand();
        if( ! ( curLine.size() == 3 && curLine == ">> " )) {
            QPlainTextEdit::keyPressEvent( evt );
        }
    }
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter: {
        if( evt->modifiers() & Qt::AltModifier ) {
            this->appendPlainText( "" );
        }
        else {
            auto str = currentCommand();
            if( str.isEmpty() ) {
                printPrompt();
            }
            else {
                emit sigDataEntered(  str.toLocal8Bit() );
                this->appendPlainText( "" );
            }
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
