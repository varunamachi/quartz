#include <QTreeView>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QModelIndex>
#include <QItemSelectionModel>

#include <core/logger/Logging.h>

#include <common/iconstore/IconFontStore.h>

#include "../QzAppContext.h"
#include "../content_manager/ContentManager.h"

#include "../selector/Node.h"
#include "../selector/TreeModel.h"
#include "ConfigPageManager.h"
#include "AbstractConfigPageProvider.h"
#include "AbstractConfigPage.h"
#include "ConfigPageSelector.h"


namespace Quartz {



const QString ConfigPageSelector::SELECTOR_ID{ "qz.config_selector" };
const QString ConfigPageSelector::SELECTOR_NAME{ "SETTINGS" };
const QString ConfigPageSelector::ADAPTER_NAME{ "qz.config_page" };


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
                        getIcon(MatIcon::Settings),
                        parent )
//    , m_data( std::make_unique< Data >( new QTreeView( this )))
    , m_data( new ConfigPageSelector::Data{ new QTreeView{ this },
                                            new TreeModel{ this }})
{
    auto layout = new QVBoxLayout();
    //deligate
    m_data->m_view->setModel( m_data->m_model );
    m_data->m_view->header()->setVisible( false );
    m_data->m_view->setRootIsDecorated(false);

    m_data->m_view->setSelectionMode( QAbstractItemView::SingleSelection );
    m_data->m_view->setSelectionBehavior( QAbstractItemView::SelectRows );
    connect( m_data->m_view->selectionModel(),
             &QItemSelectionModel::currentChanged,
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

void ConfigPageSelector::selected()
{
    const auto &selectionModel = m_data->m_view->selectionModel();
    if( selectionModel->hasSelection() ) {
        auto index = selectionModel->currentIndex();
        onSelected( index, QModelIndex{} );
    }
    else {
        if( m_data->m_model->rowCount( QModelIndex{} ) != 0 ) {
            auto index = m_data->m_model->index( 0, 0, QModelIndex{} );
            selectionModel->setCurrentIndex(
                        index,
                        QItemSelectionModel::SelectCurrent );
        }
    }
}

void ConfigPageSelector::unselected()
{

}

void ConfigPageSelector::onSelected( const QModelIndex &current,
                                     const QModelIndex &/*previous*/ )
{
    if( ! ( current.isValid() && current.internalPointer() != 0 )) {
        return;
    }
    auto node = static_cast< Node *>( current.internalPointer() );
    if( appContext()->hasContentManager()
            && appContext()->hasConfigPageManager() ) {
        appContext()->contentManager()->selectContent(
                    ConfigPageManager::CONTENT_ID );
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

const QString & ConfigPageSelector::extensionType() const
{
    return AbstractConfigPageProvider::EXTENSION_TYPE;
}

const QString & ConfigPageSelector::extensionAdapterName() const
{
    return ADAPTER_NAME;
}

bool ConfigPageSelector::handleExtension( Ext::Extension *extension )
{
    bool result = true;
    auto provider = dynamic_cast< AbstractConfigPageProvider *>( extension );
    if( provider != nullptr ) {
        auto pages = provider->configPages();
        foreach( auto page, pages ) {
            result = addPage( page ) && result;
        }
    }
    else {
        auto extensionName = extension != nullptr ? extension->extensionId()
                                            : "<null>";
        QZ_ERROR( "Qz:ConfigPageManager" )
                << "Invalid content extension provided: "
                << extensionName;
    }
    return result;
}

bool ConfigPageSelector::finalizeExtension()
{
    auto result = true;
    return result;
}


}
