
#include <QVBoxLayout>
#include <QTreeView>
#include <QHeaderView>

#include "../QzAppContext.h"
#include "../content_manager/ContentManager.h"
#include "../selector/Node.h"
#include "SelectionTree.h"
#include "GeneralSelector.h"

namespace Quartz {

const QString GeneralSelector::SELECTOR_ID{ "quartz.node_selector" };
const QString GeneralSelector::SELECTOR_NAME{ "Pages" };


struct GeneralSelector::Data
{
    explicit Data( QTreeView *treeView,
                   SelectionTree *model )
        : m_view( treeView )
        , m_model( model )
    {

    }

    QTreeView *m_view;

    SelectionTree *m_model;
};

GeneralSelector::GeneralSelector( const QzAppContext *context,
                            QWidget *parent )
    : AbstractSelector( context,
                        SELECTOR_ID,
                        SELECTOR_NAME,
                        parent )
//    , m_data( std::make_unique< Data >( new QTreeView( this )))
    , m_data( new GeneralSelector::Data( new QTreeView( this ),
                                      new SelectionTree( this )))
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
             &GeneralSelector::onSelected );
    this->setContentsMargins( QMargins{ });
    m_data->m_view->setContentsMargins( QMargins{ });
    layout->setContentsMargins( QMargins{ });
}

GeneralSelector::~GeneralSelector()
{

}

SelectionTree *GeneralSelector::model()
{
    return m_data->m_model;
}

void GeneralSelector::onSelected( const QModelIndex &index )
{
    if( ! ( index.isValid() && index.internalPointer() != 0 )) {
        return;
    }
    auto node = static_cast< Node *>( index.internalPointer() );
    if( this->context()->hasContentManager() ) {
        this->context()->contentManager()->selectContent( node->nodeId() );
    }
    emit sigNodeSelected( node );
}

}
