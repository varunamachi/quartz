
#include <core/logger/Logger.h>

#include "Node.h"
#include "AbstractNodeProvider.h"
#include "SelectionTree.h"


namespace Quartz {

struct SelectionTree::Data
{
    NodePtr m_root;

    QVector< QPair< QStringList, NodePtr >> m_pluginNodes;
};

const QString SelectionTree::ADAPTER_NAME{ "Node Tree" };

Node *SelectionTree::traverse( Node *node,
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

bool SelectionTree::addNode( const QStringList &parentPath,
                             const NodePtr node )
{
    //TODO here we have to create nodes in path if they dont exist, instead of
    //giving error
    auto result = false;
    auto *parent = createPath( m_data->m_root.get(), parentPath, 0 );
    if( parent != nullptr ) {
        parent->addChild( node );
        result = true;
    }
    return result;
}

Node * SelectionTree::createPath( Node *node,
                                  const QStringList &path,
                                  int depth )
{
    Node *result = nullptr;
    auto child = node->child( path[ depth ]);
    if( child != nullptr ) {
        auto newChild = std::make_shared< Node >( path[ depth ]);
        child = newChild.get();
        node->addChild( newChild );
    }
    ++ depth;
    if( depth == path.size() ) {
        result = child;
    }
    else {
        result = createPath( child, path, depth );
    }
    return result;
}

bool SelectionTree::removeNode( const QStringList &path )
{
    auto result = false;
    auto *parent = traverse( m_data->m_root.get(), path, true, 0 );
    if( parent != nullptr ) {
        parent->removeChild( path.last() );
        result = true;
    }
    return result;
}

bool SelectionTree::selectNode( const QStringList &path ) const
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

const Node *SelectionTree::node( const QStringList &path ) const
{
    Node *theNode = traverse( m_data->m_root.get(), path, false, 0 );
    return theNode;
}


const QString &SelectionTree::pluginType() const
{
    return  AbstractNodeProvider::PLUGIN_TYPE;
}

const QString &SelectionTree::pluginAdapterName() const
{
    return ADAPTER_NAME;
}

bool SelectionTree::handlePlugin( IPlugin *plugin )
{
    bool result = false;
    auto nodeProvider = dynamic_cast< AbstractNodeProvider *>( plugin );
    if( nodeProvider != nullptr ) {
       auto nodeInfo = nodeProvider->node();
       result = addNode( nodeInfo.first, nodeInfo.second );
       if( result ) {
           m_data->m_pluginNodes.push_back( nodeInfo );
       }
    }
    else {
        QZ_ERROR( "NodeSelector" )
                << "Invalid plugin is given to selector tree ";
    }
    return result;
}

bool SelectionTree::finalizePlugins()
{
    bool result = false;
    for( int i = 0; i < m_data->m_pluginNodes.size(); ++ i ) {
        auto pair = m_data->m_pluginNodes.at( i );
        auto &path = pair.first;
        path << pair.second->nodeId();
        result = removeNode( path );
    }
    return result;
}

QModelIndex SelectionTree::index( int row,
                                  int column,
                                  const QModelIndex &parent ) const
{
    return QModelIndex{ };
}

QModelIndex SelectionTree::parent( const QModelIndex &child ) const
{
    return QModelIndex{ };
}

int SelectionTree::rowCount( const QModelIndex &parent ) const
{
    return 0;
}

int SelectionTree::columnCount( const QModelIndex &parent ) const
{
    return 0;
}

QVariant SelectionTree::data( const QModelIndex &index, int role ) const
{
    return QVariant{ };
}


}
