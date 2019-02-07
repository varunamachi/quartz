#pragma once

#include <memory>

#include <QWidget>

#include "../../QuartzCommon.h"

namespace Quartz {

class Config;

class QUARTZ_COMMON_API GenConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GenConfigWidget(QWidget *parent = nullptr);

    ~GenConfigWidget();

    void setConfig(Config *config);

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}
