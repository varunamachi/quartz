#pragma once

#include <memory>

#include <QWidget>

namespace Quartz {

class Template;
class TemplateInstance;

namespace Plugin { namespace Creator {

/**
 * @brief The TemplateConfigWidget class allows configuring selected templates
 */
class TemplateConfigWidget : public QWidget
{
    Q_OBJECT
public:
    TemplateConfigWidget( QWidget *parent = nullptr );

    ~TemplateConfigWidget();

    void createInstanceOf( Template *tmpl );

    QVector< TemplateInstance *>  instances() const;

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

} } }
