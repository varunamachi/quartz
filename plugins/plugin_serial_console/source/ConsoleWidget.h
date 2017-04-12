#pragma once

#include <memory>

#include <QPlainTextEdit>

namespace Quartz { namespace Plugin { namespace SerialConsole {

class ConsoleWidget : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit ConsoleWidget( QWidget *parent = nullptr );

    ~ConsoleWidget();

signals:
    void sigDataEntered( const QByteArray &data );

public:
    void putData( const QByteArray &data );

    QString currentLineText();

public slots:
    void clearConsole();

protected:
    void keyPressEvent( QKeyEvent *evt ) override;

    void mousePressEvent( QMouseEvent *evt ) override;

    void mouseDoubleClickEvent( QMouseEvent *evt ) override;

    void contextMenuEvent( QContextMenuEvent *evt ) override;

private:
    void printPrompt();

    struct Data;
    std::unique_ptr< Data > m_data;

};

} } }
