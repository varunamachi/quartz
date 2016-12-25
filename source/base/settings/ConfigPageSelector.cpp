#include <QTreeView>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QModelIndex>

#include <base/QzAppContext.h>
#include <base/content_manager/ContentManager.h>

#include "../selector/Node.h"
#include "AbstractConfigNodeProvider.h"
#include "ConfigNodeTree.h"
#include "ConfigPageSelector.h"


namespace Quartz {



const QString ConfigPageSelector::SELECTOR_ID{ "quartz.config_selector" };
const QString ConfigPageSelector::SELECTOR_NAME{ "Settings" };


struct ConfigPageSelector::Data
{
    explicit Data( QTreeView *treeView,
                   ConfigNodeTree *model )
        : m_view( treeView )
        , m_model( model )
    {

    }

    QTreeView *m_view;

    ConfigNodeTree *m_model;
};

ConfigPageSelector::ConfigPageSelector( QWidget *parent )
    : AbstractSelector( SELECTOR_ID,
                        SELECTOR_NAME,
                        parent )
//    , m_data( std::make_unique< Data >( new QTreeView( this )))
    , m_data( new ConfigPageSelector::Data( new QTreeView( this ),
                                         new ConfigNodeTree( this )))
{
    auto layout = new QVBoxLayout();
    //deligate
    m_data->m_view->setModel( m_data->m_model );
    m_data->m_view->header()->setVisible( false );
    m_data->m_view->setSelectionMode( QAbstractItemView::SingleSelection );
    m_data->m_view->setSelectionBehavior( QAbstractItemView::SelectRows );
    layout->addWidget( m_data->m_view );
    this->setLayout( layout );
    connect( m_data->m_view,
             &QTreeView::clicked,
             this,
             &ConfigPageSelector::onSelected );
    this->setContentsMargins( QMargins{ });
    m_data->m_view->setContentsMargins( QMargins{ });
    layout->setContentsMargins( QMargins{ });
}

ConfigPageSelector::~ConfigPageSelector()
{

}

ConfigNodeTree *ConfigPageSelector::model()
{
    return m_data->m_model;
}

void ConfigPageSelector::onSelected( const QModelIndex &index )
{
    if( ! ( index.isValid() && index.internalPointer() != 0 )) {
        return;
    }
    auto node = static_cast< Node *>( index.internalPointer() );
    if( appContext()->hasContentManager() ) {
        appContext()->contentManager()->selectContent( node->nodeId() );
    }
    emit sigConfigNodeSelected( node );
}




}
