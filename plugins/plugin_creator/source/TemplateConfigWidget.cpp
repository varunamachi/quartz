
#include <QTreeView>
#include <QLineEdit>
#include <QSet>

#include <common/templating/Template.h>
#include <common/templating/TemplateInstance.h>
#include <common/generic_config/ui/GenConfigWidget.h>

#include "TemplateConfigWidget.h"

namespace Quartz { namespace Plugin { namespace Creator {

struct TemplateConfigWidget::Data
{
    explicit Data( TemplateConfigWidget *parent )
        : m_filter{ new QLineEdit{ parent }}
        , m_view{ new QTreeView{ parent }}
        , m_configWidget{ new GenConfigWidget{ nullptr, parent }}
    {

    }

    QLineEdit *m_filter;

    QTreeView *m_view;

    GenConfigWidget *m_configWidget;

    QVector< TemplateInstance *> m_tinsts;

    QSet< QString > m_names;

    //might need a empty genconfig object!

};

TemplateConfigWidget::TemplateConfigWidget(  QWidget *parent )
    : QWidget{ parent }
    , m_data{ new Data{ this }}
{

}

TemplateConfigWidget::~TemplateConfigWidget()
{

}

void TemplateConfigWidget::createInstanceOf( Template *tmpl )
{
    auto name = tmpl->name();
    auto index = 1;
    //If there is a name clash, we suffix numbers
    do {
        if( ! m_data->m_names.contains( name )) {
            break;
        }
        name = tmpl->name() + "_" + QString::number( index );
    } while( index <= 1000 ); //1000 should be enough
    auto inst = new TemplateInstance{name, tmpl };
    m_data->m_tinsts.append( inst );
    m_data->m_names.insert( name );
}

QVector<TemplateInstance *> TemplateConfigWidget::instances() const
{
    return m_data->m_tinsts;
}



} } }
