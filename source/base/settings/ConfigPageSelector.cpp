#include <QTreeView>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QModelIndex>

#include <core/logger/Logging.h>

#include <base/QzAppContext.h>
#include <base/content_manager/ContentManager.h>

#include "../selector/Node.h"
#include "../selector/TreeModel.h"
#include "ConfigPageManager.h"
#include "AbstractConfigPageProvider.h"
#include "AbstractConfigPage.h"
#include "ConfigPageSelector.h"


namespace Quartz {



const QString ConfigPageSelector::SELECTOR_ID{ "qz.config_selector" };
const QString ConfigPageSelector::SELECTOR_NAME{ "Settings" };
const QString ConfigPageSelector::ADAPTER_NAME{ "qz.confi_page" };


struct ConfigPageSelector::Data
{
    explicit Data( QTreeView *treeView,
                   TreeModel *model )
        : m_view( treeView )
        , m_model( model )
    {

    }

    QTreeView *m_view;

    TreeModel *m_model;
};

ConfigPageSelector::ConfigPageSelector( QWidget *parent )
    : AbstractSelector( SELECTOR_ID,
                        SELECTOR_NAME,
                        parent )
//    , m_data( std::make_unique< Data >( new QTreeView( this )))
    , m_data( new ConfigPageSelector::Data{ new QTreeView{ this },
                                            new TreeModel{ this }})
{
    auto layout = new QVBoxLayout();
    //deligate
    m_data->m_view->setModel( m_data->m_model );
    m_data->m_view->header()->setVisible( false );
    m_data->m_view->setSelectionMode( QAbstractItemView::SingleSelection );
    m_data->m_view->setSelectionBehavior( QAbstractItemView::SelectRows );
    connect( m_data->m_view,
             &QTreeView::clicked,
             this,
             &ConfigPageSelector::onSelected );
    this->setContentsMargins( QMargins{ });
    m_data->m_view->setContentsMargins( QMargins{ });
    layout->addWidget( m_data->m_view );
    layout->setContentsMargins( QMargins{ });
    this->setLayout( layout );
}

ConfigPageSelector::~ConfigPageSelector()
{

}

TreeModel * ConfigPageSelector::model()
{
    return m_data->m_model;
}

void ConfigPageSelector::onSelected( const QModelIndex &index )
{
    if( ! ( index.isValid() && index.internalPointer() != 0 )) {
        return;
    }
    auto node = static_cast< Node *>( index.internalPointer() );
    if( appContext()->hasConfigPageManager() ) {
        appContext()->configPageManager()->selectPage( node->nodeId() );
    }
    emit sigConfigNodeSelected( node );
}

bool ConfigPageSelector::addPage( AbstractConfigPage *page )
{
    bool result = false;
    if( appContext()->hasConfigPageManager() ) {
        result = m_data->m_model->addNode( page->parentPath(),
                                           page->configPageName(),
                                           page->configPageId(),
                                           page->icon() );
        result = result && appContext()->configPageManager()->addPage( page );
        //need to remove node if above step fails
    }
    return result;
}

const QString & ConfigPageSelector::pluginType() const
{
    return AbstractConfigPageProvider::PLUGIN_TYPE;
}

const QString & ConfigPageSelector::pluginAdapterName() const
{
    return ADAPTER_NAME;
}

bool ConfigPageSelector::handlePlugin( AbstractPlugin *plugin )
{
    bool result = true;
    auto provider = dynamic_cast< AbstractConfigPageProvider *>( plugin );
    if( provider != nullptr ) {
        auto pages = provider->configPages();
        foreach( auto page, pages ) {
            result = addPage( page ) && result;
        }
    }
    else {
        auto pluginName = plugin != nullptr ? plugin->pluginId()
                                            : "<null>";
        QZ_ERROR( "Qz:ConfigPageManager" )
                << "Invalid content plugin provided: "
                << pluginName;
    }
    return result;
}

bool ConfigPageSelector::finalizePlugins()
{
    auto result = true;
    return result;
}


}
