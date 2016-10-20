
#include <QVBoxLayout>

#include "NodeSelector.h"
#include "Node.h"

namespace Quartz {


struct NodeSelector::Data
{
    NodePtr m_root;

    QVector< QPair< QStringList, NodePtr >> m_path;
};

const QString NodeSelector::SELECTOR_ID{ "quartz.node_selector" };
const QString NodeSelector::SELECTOR_NAME{ "Pages" };
const QString NodeSelector::ADAPTER_NAME{ "Node Selector" };
const QString NodeSelector::PLUGIN_TYPE{ "quartz.node" };

NodeSelector::NodeSelector( QWidget *parent )
    : AbstractSelector( SELECTOR_ID,
                        SELECTOR_NAME,
                        parent )
{

}

NodeSelector::~NodeSelector()
{

}

Node *NodeSelector::traverse( Node *node,
                              const QStringList &path,
                              bool tillParent,
                              int depth ) const
{
    Node *result = nullptr;
    auto child = node->child( path[ depth ]);
    if( child != nullptr ) {
        ++ depth;
        if( tillParent && depth == path.size() - 1 ) {
            result = child;
        }
        else if( depth == path.size() ) {
            result = child;
        }
        else {
            result = traverse( child, path, tillParent, depth );
        }
    }
    return result;
}

bool NodeSelector::addNode( const QStringList &parentPath,
                            const NodePtr node )
{
    auto result = false;
    auto *parent = traverse( m_data->m_root.get(), parentPath, false, 0 );
    if( parent != nullptr ) {
        parent->addChild( node );
        result = true;
    }
    return result;
}

bool NodeSelector::removeNode( const QStringList &path )
{
    auto result = false;
    auto *parent = traverse( m_data->m_root.get(), path, true, 0 );
    if( parent != nullptr ) {
        parent->removeChild( path.last() );
        result = true;
    }
    return result;
}

bool NodeSelector::selectNode( const QStringList &path ) const
{
    bool result = false;
    auto sel = this->node( path );
    if( sel != nullptr ) {
//        contentManager()->select( sel->nodeId() );
        sel->nodeId();
        result = true;
    }
    return result;
}

const Node *NodeSelector::node( const QStringList &path ) const
{
    Node *theNode = traverse( m_data->m_root.get(), path, false, 0 );
    return theNode;
}

const QString &NodeSelector::pluginType() const
{
    return  PLUGIN_TYPE;
}

const QString &NodeSelector::pluginAdapterName() const
{
    return ADAPTER_NAME;
}

bool NodeSelector::handlePlugin( IPlugin *plugin )
{
    return false;
}

bool NodeSelector::finalizePlugins()
{
    return false;
}

void NodeSelector::setupLayout()
{

}

QModelIndex NodeSelector::index( int row,
                                 int column,
                                 const QModelIndex &parent ) const
{
    return QModelIndex{ };
}

QModelIndex NodeSelector::parent( const QModelIndex &child ) const
{
    return QModelIndex{ };
}

int NodeSelector::rowCount( const QModelIndex &parent ) const
{
    return 0;
}

int NodeSelector::columnCount( const QModelIndex &parent ) const
{
    return 0;
}

QVariant NodeSelector::data( const QModelIndex &index, int role ) const
{
    return QVariant{ };
}


}
