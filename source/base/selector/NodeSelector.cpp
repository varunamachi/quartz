
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
                              int depth )
{
    Node *result = nullptr;
    if( node != nullptr ) {
        if( path.size() == depth ) {
            result = node;
        }
        else if( path[ depth ] != node->nodeId() ) {
            result = nullptr;
        }
        else {
            ++ depth;
            for( int i = 0; i < node->numChildren(); ++ i ) {
                Node * child = node->nodeAt( i );
                result = traverse( child, path, depth );
                if( result != nullptr ) {
                    break;
                }
            }
        }
    }
    return node;
}

void NodeSelector::addNode( const QStringList &parentPath,
                            const NodePtr node )
{
    Node *node = m_data->m_root;
}

void NodeSelector::removeNode( const QStringList &parentPath,
                               const QString &nodeId )
{

}

void NodeSelector::selectNode( const QStringList &path,
                               const QString &nodeId ) const
{

}

const Node *NodeSelector::node( const QStringList &path,
                                const QString &nodeId )
{

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
