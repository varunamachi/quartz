#pragma once

#include <memory>

#include <QWidget>

namespace Quartz {

class Config;

class GenConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GenConfigWidget( Config *config, QWidget *parent = nullptr );

    ~GenConfigWidget();

    void setConfig( Config *config );

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
