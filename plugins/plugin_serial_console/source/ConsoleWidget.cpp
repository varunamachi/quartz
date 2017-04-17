
#include <QTextBlock>

#include <plugin_base/BundleLoggin.h>

#include "ConsoleWidget.h"

//Taken from Qt example

namespace Quartz { namespace Plugin { namespace SerialConsole {

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
        return m_historyIndex >= 0 && m_historyIndex < m_history.size();
    }

    inline void incrementHistoryIndex()
    {
        if( m_historyIndex < m_history.size() - 1 ) {
            ++ m_historyIndex;
        }
        QZP_TRACE << "** INC: " << m_historyIndex
                  << " : " << m_history.size();
    }

    inline void decrementHistoryIndex()
    {
        if( m_historyIndex > 0 ) {
            -- m_historyIndex;
        }
        QZP_TRACE << "### DEC: " << m_historyIndex
                  << " : " << m_history.size();
    }

    inline void resetHistoryIndex()
    {
        m_historyIndex = m_history.size() - 1;
    }

    inline void addHistory( const QString &historyItem )
    {
        if( m_history.isEmpty() || m_history.last() != historyItem ) {
            m_history.push_back( historyItem );
        }
        m_historyDirection = HistoryDirection::None;
    }

    inline void adjustLastHistoryIndex()
    {
//        if( m_historyIndex == 0 ) {
//            incrementHistoryIndex();
//        }
//        if( m_historyIndex == m_history.size() - 1 ) {
//            decrementHistoryIndex();
//        }
    }

    inline QString history() const
    {
        if( m_historyIndex < m_history.size() ) {
            return m_history[ m_historyIndex ];
        }
        return QStringLiteral( "" );
    }

    int m_historyIndex;

    int m_pos;

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
    this->moveCursor( QTextCursor::End );
    this->insertPlainText( data );
    this->moveCursor( QTextCursor::End );
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
        return cmd.mid( 3 );
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
    auto cursor = this->textCursor();
    auto endCursor = cursor;
    endCursor.movePosition( QTextCursor::End );
    cursor.setPosition( m_data->m_pos, QTextCursor::MoveAnchor );
    cursor.setPosition( endCursor.position(), QTextCursor::KeepAnchor );
    cursor.insertText( cmd );
    this->setTextCursor( cursor );
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
        if( m_data->isHistoryIndexValid()) {
            m_data->adjustLastHistoryIndex();
            auto prev = m_data->history();
            insertCommand( prev );
            m_data->decrementHistoryIndex();
            m_data->m_historyDirection = HistoryDirection::Backward;
        }
    }
        break;
    case Qt::Key_Down: {
        if( m_data->m_historyIndex == m_data->m_history.size() ) {
            insertCommand( "" );
            m_data->resetHistoryIndex();
        }
        else if( m_data->isHistoryIndexValid() ) {
            m_data->adjustLastHistoryIndex();
            auto prev = m_data->history();
            insertCommand( prev );
            m_data->incrementHistoryIndex();
            m_data->m_historyDirection = HistoryDirection::Forward;
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
                emit sigDataEntered(  ( str  + "\r\n" ).toLocal8Bit() );
                if( ! str.isEmpty() ) {
                    m_data->addHistory( str );
                    m_data->resetHistoryIndex();
                    this->appendPlainText( "" );
                }
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
    m_data->m_pos = this->textCursor().position();

}

} } }
