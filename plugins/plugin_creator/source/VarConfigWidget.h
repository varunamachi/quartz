#pragma once

#include <memory>

#include <QWidget>

namespace Quartz {

class TemplateInstance;

namespace Plugin { namespace Creator {

class VarConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VarConfigWidget(  TemplateInstance *templInst ,
                               QWidget *parent = nullptr );

    ~VarConfigWidget();

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};
} } }
