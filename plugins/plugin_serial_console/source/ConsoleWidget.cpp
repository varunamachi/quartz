
#include <QTextBlock>

#include "ConsoleWidget.h"

//Taken from Qt example

namespace Quartz { namespace Plugin { namespace SerialConsole {

struct ConsoleWidget::Data
{
    explicit Data( QWidget */*parent*/ )
        : m_historyIndex{ 0 }
    {

    }

    int m_historyIndex;

    QTextCursor m_cursor;

    QVector< QString > m_history;
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
    int line = doc->lineCount() - 1;
    QString cmd = "";
    while( line >= 0 ) {
        auto block = doc->findBlockByLineNumber( line );
        auto txt = block.text();
        cmd = txt + cmd;
        if( txt.startsWith( ">> " ) || txt.isEmpty() ) {
            break;
        }
        -- line;
    }
    cmd = cmd.trimmed();
    if( ! cmd.isEmpty() ) {
        return cmd.mid( 3 ) + "\r\n";
    }
    return cmd;
}

QString ConsoleWidget::currentLine()
{
    auto doc = this->document();
    int curLine = doc->lineCount() - 1;
    auto txt = doc->findBlockByLineNumber( curLine );
    return txt.text();
}

void ConsoleWidget::insertCommand( const QString &cmd )
{
//    this->moveCursor( QTextCursor::StartOfLine );
//    auto cursor = this->textCursor();
//    cursor.insertText()
//    cursor.movePosition( QTextCursor::NextCharacter,
//                         QTextCursor::MoveAnchor,
//                         3 );
//    this->setTextCursor( cursor );
}

void ConsoleWidget::clearConsole()
{
    clear();
    printPrompt();
}

void ConsoleWidget::keyPressEvent( QKeyEvent *evt )
{
    switch (evt->key()) {
    case Qt::Key_Up: {
        if( m_data->m_historyIndex > 0
                && m_data->m_historyIndex < m_data->m_history.size() ) {
            -- m_data->m_historyIndex;
            auto prev = m_data->m_history[ m_data->m_historyIndex ];
            insertCommand( prev );
        }
    }
        break;
    case Qt::Key_Down: {
        if( m_data->m_historyIndex > 0
                && m_data->m_historyIndex < m_data->m_history.size() - 1 ) {
            ++ m_data->m_historyIndex;
            auto prev = m_data->m_history[ m_data->m_historyIndex ];
            insertCommand( prev );
        }
    }
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

    case Qt::Key_Left:
    case Qt::Key_Backspace: {
        auto curLine = currentLine();
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
                m_data->m_history.push_back( str );
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
    auto cursor = this->textCursor();
    cursor.movePosition( QTextCursor::End );
    m_data->m_cursor = cursor;

}

} } }
