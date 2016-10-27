
#include <QVBoxLayout>
#include <QTreeView>

#include "Node.h"
#include "SelectionTree.h"
#include "NodeSelector.h"

namespace Quartz {

const QString NodeSelector::SELECTOR_ID{ "quartz.node_selector" };
const QString NodeSelector::SELECTOR_NAME{ "Pages" };


struct NodeSelector::Data
{
    explicit Data( QTreeView *treeView )
        : m_view( treeView )
    {

    }

    QTreeView *m_view;
};

NodeSelector::NodeSelector( QWidget *parent )
    : AbstractSelector( SELECTOR_ID,
                        SELECTOR_NAME,
                        parent )
//    , m_data( std::make_unique< Data >( new QTreeView( this )))
    , m_data( new NodeSelector::Data( new QTreeView( this )))
{
    auto layout = new QVBoxLayout();
    auto tree = new SelectionTree( this );
    //deligate
    m_data->m_view->setModel( tree );
    layout->addWidget( m_data->m_view );
    this->setLayout( layout );
    connect( m_data->m_view,
             &QTreeView::activated,
             this,
             &NodeSelector::onSelected );
}

NodeSelector::~NodeSelector()
{

}

void NodeSelector::onSelected( const QModelIndex &index )
{
    if( ! ( index.isValid() && index.internalPointer() != 0 )) {
        return;
    }
    auto node = static_cast< Node *>( index.internalPointer() );
    emit sigNodeSelected( node );
}

}
