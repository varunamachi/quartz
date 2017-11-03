
#include <QSet>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTreeView>
#include <QLineEdit>

#include <common/templating/Template.h>
#include <common/templating/TemplateInstance.h>
#include <common/model_view/ArrayModel.h>
#include <common/generic_config/ui/GenConfigWidget.h>

#include "TemplateConfigWidget.h"

namespace Quartz { namespace Plugin { namespace Creator {

struct TemplateConfigWidget::Data
{
    explicit Data( TemplateConfigWidget *parent )
        : m_filter{ new QLineEdit{ parent }}
        , m_view{ new QTreeView{ parent }}
        , m_configWidget{ new GenConfigWidget{ nullptr, parent }}
        , m_tmodel{ new ArrayModel{ parent }}
    {

    }

    QLineEdit *m_filter;

    QTreeView *m_view;

    GenConfigWidget *m_configWidget;

    QVector< ITreeNode *> m_tinsts;

    QSet< QString > m_names;

    ArrayModel *m_tmodel;

    //might need a empty genconfig object!

};

TemplateConfigWidget::TemplateConfigWidget(  QWidget *parent )
    : QWidget{ parent }
    , m_data{ new Data{ this }}
{
    auto mainLayout = new QHBoxLayout{};
    auto leftLayout = new QVBoxLayout{};
    leftLayout->addWidget( m_data->m_filter );
    leftLayout->addWidget( m_data->m_view );
    mainLayout->addLayout( leftLayout );
    mainLayout->addWidget( m_data->m_configWidget );

    m_data->m_tmodel->setRoots( m_data->m_tinsts );
    m_data->m_view->setModel( m_data->m_tmodel );

    mainLayout->setContentsMargins( QMargins{} );
    leftLayout->setContentsMargins( QMargins{} );

    this->setLayout( mainLayout );
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

int TemplateConfigWidget::numInstances() const
{
    return m_data->m_tinsts.size();
}

TemplateInstance * TemplateConfigWidget::instanceAt(int index)
{
    TemplateInstance *tinst = nullptr;
    if( index < m_data->m_tinsts.size() ) {
        tinst = static_cast< TemplateInstance *>( m_data->m_tinsts.at( index ));
    }
    return tinst;
}


void TemplateConfigWidget::clear()
{
    m_data->m_tinsts.clear();
    m_data->m_names.clear();
    m_data->m_configWidget->setConfig( nullptr );
}



} } }
