
#include <QSet>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QAction>
#include <QPushButton>

#include <core/logger/Logging.h>

#include <common/templating/Template.h>
#include <common/templating/TemplateInstance.h>
#include <common/model_view/ArrayModel.h>
#include <common/model_view/BasicSortFilter.h>
#include <common/generic_config/ui/GenConfigDelegate.h>
#include <common/generic_config/model/Config.h>
#include <common/generic_config/model/Param.h>
#include <common/widgets/QzTreeView.h>

#include "TemplateConfigWidget.h"

namespace Quartz { namespace Ext { namespace Creator {

const QVector< QString > TI_HEADERS{
    QObject::tr( "Instance" )
};

struct TemplateConfigWidget::Data
{
    explicit Data( TemplateConfigWidget *parent )
        : m_filter{ new QLineEdit{ parent }}
        , m_configFilter{ new QLineEdit{ parent }}
        , m_view{ new QzTreeView{ parent }}
        , m_emptyConfig{ "none", "None" }
        , m_configView{ new QzTreeView{ parent }}
        , m_tmodel{ new ArrayModel{ 2, false, true, TI_HEADERS, parent }}
        , m_configModel{ new ConfigModel{ parent }}
        , m_configProxy{ new BasicSortFilter{ parent }}
        , m_instanceProxy{ new BasicSortFilter{ parent }}
    {

    }

    QLineEdit *m_filter;

    QLineEdit *m_configFilter;

    QzTreeView *m_view;

    Config m_emptyConfig;

    QzTreeView *m_configView;

    ArrayModel *m_tmodel;

    ConfigModel *m_configModel;

    BasicSortFilter *m_configProxy;

    BasicSortFilter *m_instanceProxy;

    QHash< QString, std::shared_ptr< TemplateInstance >> m_instances;
};

TemplateConfigWidget::TemplateConfigWidget(  QWidget *parent )
    : QWidget{ parent }
    , m_data{ new Data{ this }}
{
    auto clearBtn = new QPushButton{ tr( "Clear" ), this };
    auto lblyt = new QHBoxLayout{};
    lblyt->addStretch();
    lblyt->addWidget( clearBtn );

    auto leftLayout = new QVBoxLayout{};
    leftLayout->addWidget( m_data->m_filter );
    leftLayout->addWidget( m_data->m_view );
    leftLayout->addLayout( lblyt );

    auto rightLayout = new QVBoxLayout{};
    rightLayout->addWidget( m_data->m_configFilter );
    rightLayout->addWidget( m_data->m_configView );

    auto mainLayout = new QHBoxLayout{};
    mainLayout->addLayout( leftLayout );
    mainLayout->addLayout( rightLayout );

    auto proxy = new BasicSortFilter{ this };
    proxy->setSourceModel( m_data->m_tmodel );
    auto configProxy = new BasicSortFilter{ this };
    configProxy->setSourceModel( m_data->m_configModel );

    m_data->m_view->setModel( proxy );
    m_data->m_view->setRootIsDecorated( false );
    m_data->m_configView->setModel( configProxy );
    m_data->m_configView->setRootIsDecorated( false );
    m_data->m_configView->setItemDelegate( new GenConfigDelegate{ this });

    this->setLayout( mainLayout );
    mainLayout->setContentsMargins( QMargins{} );
    leftLayout->setContentsMargins( QMargins{} );

    connect( m_data->m_view->selectionModel(),
             &QItemSelectionModel::currentChanged,
             [ this ]( const QModelIndex &current, const QModelIndex & ){
        auto ti = static_cast< TemplateInstance *>( current.internalPointer() );
        if( ti != nullptr ) {
            if( ti->instanceOf()->config() != nullptr ) {
                m_data->m_configModel->setConfig( ti->instanceConfig() );
            } else {
                m_data->m_configModel->setConfig( &m_data->m_emptyConfig );
            }
        }
    });
    connect( clearBtn,
             &QPushButton::clicked,
             m_data->m_tmodel,
             &ArrayModel::clear );
    connect( m_data->m_filter,
             &QLineEdit::textChanged,
             proxy,
             &BasicSortFilter::setExpression );
    connect( m_data->m_configFilter,
             &QLineEdit::textChanged,
             configProxy,
             &BasicSortFilter::setExpression );

    auto action = [ this ]( QModelIndex i ) {
        m_data->m_tmodel->removeRoot(
                    static_cast< TreeNode *>( i.internalPointer() ));
    };
    m_data->m_view->addContextAction({ tr( "Delete" ), action });
}

TemplateConfigWidget::~TemplateConfigWidget()
{

}

TemplateInstance * TemplateConfigWidget::createInstanceOf( Template *tmpl )
{
    auto name = tmpl->name();
    auto index = 1;
    //If there is a name clash, we suffix numbers
    do {
        if( ! m_data->m_instances.contains( name )) {
            break;
        }
        name = tmpl->name() + "_" + QString::number( index );
        ++ index;
    } while( index <= 1000 ); //1000 should be enough
    auto inst = std::make_shared< TemplateInstance >(
                name,
                tmpl->config()->clone(),
                tmpl );
    m_data->m_instances.insert( name, inst );
    m_data->m_tmodel->addRoot( inst.get() );
    return inst.get();
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
    m_data->m_configModel->setConfig( &m_data->m_emptyConfig );
}

//////////////////////// Config Model ///////////////////////////

const QVector< QString > CONFIG_HEADERS{
    QObject::tr( "Name" ),
    QObject::tr( "Value" )
};

ConfigModel::ConfigModel( QObject *parent )
    : AbstractTreeModel{
          parent,
          AbstractTreeModel::Options{ 2, false, true, CONFIG_HEADERS }}
    , m_config{ nullptr }
{

}

ConfigModel::~ConfigModel()
{

}

void ConfigModel::setConfig( Config *config )
{
    beginResetModel();
    m_config = config;
    endResetModel();
}

TreeNode * ConfigModel::rootAt( int index ) const
{
    if( m_config != nullptr && index < m_config->numChildParams() ) {
        return m_config->childParamAt( index );
    }
    return nullptr;
}

int ConfigModel::rootCount() const
{
    if( m_config != nullptr ) {
        return m_config->numChildParams();
    }
    return 0;
}


} } }
