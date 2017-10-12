#pragma once

#include <memory>

#include <QWidget>

namespace Quartz { namespace Plugin { namespace Creator {


class TemplateConfigWidget : public QWidget
{
    Q_OBJECT
public:
    TemplateConfigWidget( QWidget *parent = nullptr );

    ~TemplateConfigWidget();

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

} } }
