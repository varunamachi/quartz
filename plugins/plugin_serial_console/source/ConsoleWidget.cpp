#include <QTextBlock>

#include <plugin_base/PluginLogging.h>

#include "ConsoleWidget.h"

//Taken from Qt example

namespace Quartz { namespace Ext { namespace SerialConsole {

enum class HistoryDirection
{
    Backward,
    Forward,
    None
};

struct ConsoleWidget::Data
{
    explicit Data( QWidget */*parent*/ )
        : m_historyIndex{ 0 }
        , m_historyDirection{ HistoryDirection::None }
    {

    }

    inline bool isHistoryIndexValid() const
    {
        return ! m_history.isEmpty()
                && m_historyIndex >= 0 && m_historyIndex <= m_history.size();
    }

    inline void addHistory( const QString &historyItem )
    {
        if( m_history.isEmpty() || m_history.last() != historyItem ) {
            m_history.push_back( historyItem );
        }
        m_historyIndex = m_history.size();
        m_historyDirection = HistoryDirection::None;
    }

    inline QString history() const
    {
        if( m_historyIndex < m_history.size() ) {
            return m_history[ m_historyIndex ];
        }
        return QStringLiteral( "" );
    }

    QString nextCommand()
    {
        if( isHistoryIndexValid() ) {
            if( m_historyIndex < m_history.size() ) {
                ++ m_historyIndex;
            }
            m_historyDirection = HistoryDirection::Forward;
        }
        return history();
    }

    QString prevCommand()
    {
        if( isHistoryIndexValid()) {
            if( m_historyIndex > 0 ) {
                -- m_historyIndex;
            }
            m_historyDirection = HistoryDirection::Backward;
        }
        return history();
    }

    int m_historyIndex;

    int m_pos;

    int m_curLinePos;

    HistoryDirection m_historyDirection;

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
    setPalette( p );
    printPrompt();
#ifdef Q_OS_WIN
    this->setFont( QFont{ "Consolas", 12 });
#else
    this->setFont( QFont{ "Ubuntu Mono", 12 });
#endif

}

ConsoleWidget::~ConsoleWidget()
{

}

void ConsoleWidget::putData( const QByteArray &data )
{
    this->moveCursor( QTextCursor::End );
    this->insertPlainText( data );
    this->moveCursor( QTextCursor::End );
    m_data->m_pos = this->textCursor().position();
    m_data->m_curLinePos = this->textCursor().position();
}

QString ConsoleWidget::currentCommand()
{
    auto cursor = this->textCursor();
    auto endCursor = cursor;
    endCursor.movePosition( QTextCursor::End );
    cursor.setPosition( m_data->m_pos, QTextCursor::MoveAnchor );
    cursor.setPosition( endCursor.position(), QTextCursor::KeepAnchor );
    auto selected = cursor.selectedText();
    cursor.clearSelection();
    return selected;
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
    auto cursor = this->textCursor();
    auto endCursor = cursor;
    endCursor.movePosition( QTextCursor::End );
    cursor.setPosition( m_data->m_pos, QTextCursor::MoveAnchor );
    cursor.setPosition( endCursor.position(), QTextCursor::KeepAnchor );
    cursor.insertText( cmd );
    this->setTextCursor( cursor );
    cursor.movePosition( QTextCursor::StartOfLine );
    m_data->m_curLinePos = cursor.position();
}

void ConsoleWidget::clearConsole()
{
    clear();
    printPrompt();
}

void ConsoleWidget::clearHistory()
{
    m_data->m_history.clear();
    m_data->m_historyIndex = 0;
}

void ConsoleWidget::keyPressEvent( QKeyEvent *evt )
{
    switch (evt->key()) {
    case Qt::Key_Up: {
        auto prev = m_data->prevCommand();
        if( ! prev.isEmpty() ) {
            insertCommand( prev );
        }
    }
        break;
    case Qt::Key_Down: {
        auto prev = m_data->nextCommand();
        insertCommand( prev );
    }
        break;
    case Qt::Key_Home: {
        auto cursor = this->textCursor();
        if( evt->modifiers() & Qt::CTRL ) {
            cursor.setPosition( m_data->m_pos );
        }
        else {
            cursor.setPosition( m_data->m_curLinePos );
        }
        this->setTextCursor( cursor );
    }
        break;
    case Qt::Key_End: {
        auto cursor = this->textCursor();
        if( evt->modifiers() & Qt::CTRL ) {
            cursor.movePosition( QTextCursor::End );
        }
        else {
            cursor.movePosition( QTextCursor::EndOfLine );
        }
        this->setTextCursor( cursor );
    }
        break;

    case Qt::Key_Left:
    case Qt::Key_Backspace: {
        if( this->textCursor().position() > m_data->m_pos ) {
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
            if( ! str.isEmpty() ) {
                auto cmd = str.trimmed() + "\r\n";
                emit sigDataEntered(  cmd.toLocal8Bit() );
                m_data->addHistory( str );
                this->appendPlainText( "" );
                m_data->m_pos = this->textCursor().position();
            }
            printPrompt();
        }
        m_data->m_curLinePos = this->textCursor().position();
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
                QString{ "<font color = 'red'><b>\n>></b></font> " });
    auto cur = this->textCursor();
    cur.movePosition( QTextCursor::End, QTextCursor::MoveAnchor );
    this->setTextCursor( cur );
    m_data->m_pos = cur.position();
    m_data->m_curLinePos = m_data->m_pos;

}

} } }
