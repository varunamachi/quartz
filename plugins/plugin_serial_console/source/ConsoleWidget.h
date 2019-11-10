#pragma once

#include <memory>

#include <QPlainTextEdit>

namespace Quartz { namespace Ext { namespace SerialConsole {

class ConsoleWidget : public QPlainTextEdit {
    Q_OBJECT
public:
    explicit ConsoleWidget(QWidget* parent = nullptr);

    ~ConsoleWidget();

signals:
    void sigDataEntered(const QByteArray& data);

public:
    void putData(const QByteArray& data);

    QString currentCommand();

public slots:
    void clearConsole();

    void clearHistory();

protected:
    void keyPressEvent(QKeyEvent* evt) override;

    void mousePressEvent(QMouseEvent* evt) override;

    void mouseDoubleClickEvent(QMouseEvent* evt) override;

    void contextMenuEvent(QContextMenuEvent* evt) override;

private:
    QString currentLine();

    void insertCommand(const QString& cmd);

private:
    void printPrompt();

    struct Data;
    std::unique_ptr<Data> m_data;
};

}}} // namespace Quartz::Ext::SerialConsole
