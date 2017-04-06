#pragma once

#include <memory>

#include <QTextEdit>

namespace Quartz { namespace Plugin { namespace SerialConsole {

class ConsoleWidget : public QTextEdit
{
    Q_OBJECT
public:
    explicit ConsoleWidget( QWidget *parent = nullptr );

    ~ConsoleWidget();

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

} } }
