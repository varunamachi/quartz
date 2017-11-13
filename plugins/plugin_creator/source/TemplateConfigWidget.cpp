
#include <QSet>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTreeView>

#include <common/templating/Template.h>
#include <common/templating/TemplateInstance.h>
#include <common/model_view/ArrayModel.h>
#include <common/generic_config/ui/GenConfigWidget.h>
#include <common/generic_config/model/Config.h>

#include "TemplateConfigWidget.h"

namespace Quartz { namespace Plugin { namespace Creator {

struct TemplateConfigWidget::Data
{
    explicit Data( TemplateConfigWidget *parent )
        : m_filter{ new QLineEdit{ parent }}
        , m_view{ new QTreeView{ parent }}
        , m_emptyConfig{ "none", "None" }
        , m_configWidget{ new GenConfigWidget{ &m_emptyConfig, parent }}
        , m_tmodel{ new ArrayModel{ 2, false, parent }}
    {

    }

    QLineEdit *m_filter;

    QTreeView *m_view;

    Config m_emptyConfig;

    GenConfigWidget *m_configWidget;

    ArrayModel *m_tmodel;

    QHash< QString, std::shared_ptr< TemplateInstance >> m_instances;
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

    m_data->m_view->setModel( m_data->m_tmodel );
    m_data->m_view->setRootIsDecorated( false );

    mainLayout->setContentsMargins( QMargins{} );
    leftLayout->setContentsMargins( QMargins{} );

    this->setLayout( mainLayout );

    connect( m_data->m_view->selectionModel(),
             &QItemSelectionModel::currentChanged,
             [ this ]( const QModelIndex &current, const QModelIndex &){
        auto ti = static_cast< TemplateInstance *>(
                    current.internalPointer() );
        if( ti != nullptr ) {
            if( ti->instanceOf()->config() != nullptr ) {
                m_data->m_configWidget->setConfig(
                            ti->instanceOf()->config() );
            } else {
                m_data->m_configWidget->setConfig( &m_data->m_emptyConfig );
            }
        }
    });
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
        if( ! m_data->m_instances.contains( name )) {
            break;
        }
        name = tmpl->name() + "_" + QString::number( index );
    } while( index <= 1000 ); //1000 should be enough
    auto inst = std::make_shared< TemplateInstance >( name, tmpl );
    m_data->m_instances.insert( name, inst );
    m_data->m_tmodel->addRoot( inst.get() );
}

int TemplateConfigWidget::numInstances() const
{
    return m_data->m_tmodel->rootCount();
}

TemplateInstance * TemplateConfigWidget::instanceAt( int index )
{
    TemplateInstance *tinst = nullptr;
    if( index < m_data->m_tmodel->rootCount() ) {
        tinst = static_cast< TemplateInstance * >(
                    m_data->m_tmodel->rootAt( index ));
    }
    return tinst;
}

void TemplateConfigWidget::clear()
{
    m_data->m_tmodel->clear();
    m_data->m_instances.clear();
    m_data->m_configWidget->setConfig( &m_data->m_emptyConfig );
}

} } }
