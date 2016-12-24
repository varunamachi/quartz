
#include <core/logger/Logging.h>

#include "../selector/Node.h"
#include "AbstractGeneralNodeProvider.h"
#include "SelectionTree.h"


namespace Quartz {

struct SelectionTree::Data
{
    Data()
        : m_root{ new Node{ nullptr, "root", "Root" }}
    {

    }

    NodePtr m_root;

    QVector< std::shared_ptr< NodeInfo >> m_pluginNodes;
};

const QString SelectionTree::ADAPTER_NAME{ "Node Tree" };

static QString makeNodeId( const QStringList &path,
                           const QString name = QString{ "" },
                           int depth = -1 )
{
    depth = depth == -1 ? path.size() : depth;
    QString nodeId{ "#page." };
    for( int i = 0; i < depth; ++ i ) {
        nodeId.append( path[ i ]).append( "." );
    }
    nodeId.append( name );
    return nodeId;
}

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

SelectionTree::SelectionTree( QObject *parent )
//    : m_data( std::make_unique< Data >() )
    : QAbstractItemModel( parent )
    , m_data( new Data{} )
{

}

SelectionTree::~SelectionTree()
{

}

Node * SelectionTree::addNode( const QStringList &parentPath,
                               const QString &nodeName,
                               const QString &nodeId,
                               QIcon icon )
{
    QString id = nodeId.isEmpty() ? makeNodeId( parentPath, nodeName )
                                  : nodeId;
    auto node = std::make_shared< Node >( m_data->m_root.get(),
                                          id,
                                          nodeName,
                                          icon );
    if( addNode( parentPath, node )) {
        return node.get();
    }
    return nullptr;
}

bool SelectionTree::addNode( const QStringList &parentPath,
                             const NodePtr node )
{
    auto result = false;
    auto *parent = m_data->m_root.get();
    if( ! parentPath.empty() ) {
        parent = createPath( m_data->m_root.get(), parentPath, 0 );
    }
    if( parent != nullptr ) {
        parent->addChild( node );
        node->setParent( parent );
        result = true;
    }
    return result;
}

Node * SelectionTree::createPath( Node *node,
                                  const QStringList &path,
                                  int depth )
{
    Node *result = nullptr;
    auto child = node->child( path[ depth ]); //pathID
    if( child == nullptr ) {
        auto childId = makeNodeId( path, path[ depth ], depth );
        auto newChild = std::make_shared< Node >( node, childId, path[ depth ]);
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
    return  AbstractGeneralNodeProvider::PLUGIN_TYPE;
}

const QString &SelectionTree::pluginAdapterName() const
{
    return ADAPTER_NAME;
}

bool SelectionTree::handlePlugin( AbstractPlugin *plugin )
{
    bool result = true;
    auto nodeProvider = dynamic_cast< AbstractGeneralNodeProvider *>( plugin );
    if( nodeProvider != nullptr ) {
       auto nodes = nodeProvider->nodes();
       foreach( auto nodeInfo, nodes ) {
           auto res = addNode( nodeInfo->m_nodePath,
                               nodeInfo->m_nodeName,
                               nodeInfo->m_nodeId,
                               nodeInfo->m_nodeIcon );
           if( res ) {
               m_data->m_pluginNodes.push_back( nodeInfo );
           }
           result = res && result;
       }
    }
    else {
        auto pluginName = plugin != nullptr ? plugin->pluginId()
                                            : "<null>";
        QZ_ERROR( "Qz:NodeSelector" )
                << "Invalid node plugin provided: " << pluginName;
    }
    return result;
}

bool SelectionTree::finalizePlugins()
{
    bool result = false;
    m_data->m_pluginNodes.clear();
    return result;
}

QModelIndex SelectionTree::index( int row,
                                  int column,
                                  const QModelIndex &parent ) const
{
    if( ! hasIndex( row, column, parent )) {
        return QModelIndex();
    }
    QModelIndex index{ };
    auto node = m_data->m_root.get();
    if( parent.isValid() ) {
        node = static_cast< Node * >( parent.internalPointer() );
    }
    auto child = node->childAt( row );
    if( child != nullptr ) {
        index = createIndex( row, column, child );
    }
    return index;
}

QModelIndex SelectionTree::parent( const QModelIndex &childIndex ) const
{
    if( ! childIndex.isValid() ) {
        return QModelIndex();
    }
    auto child = static_cast< Node * >( childIndex.internalPointer() );
    auto parent = child->parent();
    QModelIndex parentIndex{ };
    if( parent != m_data->m_root.get() ) {
        auto gprnt = parent->parent();
        parentIndex = createIndex( gprnt->indexOfChild( parent ),
                                   0,
                                   parent );
    }
    return parentIndex;
}

int SelectionTree::rowCount( const QModelIndex &parent ) const
{
    if( parent.column() > 0 ) {
        return 0;
    }
    int rows = 0;
    auto node = m_data->m_root.get();
    if( parent.isValid() ) {
        node = static_cast< Node *>( parent.internalPointer() );
    }
    rows = static_cast< int >( node->numChildren() );
    return rows;
}

int SelectionTree::columnCount( const QModelIndex &/*parent*/ ) const
{
    return 1;
}

QVariant SelectionTree::data( const QModelIndex &index, int role ) const
{
    QVariant data { };
    if( index.isValid() ) {
        if( role == Qt::DisplayRole ) {
            auto node = static_cast< Node *>( index.internalPointer() );
            data = node->nodeName();
        }
    }
    return data;
}

bool SelectionTree::hasChildren( const QModelIndex &parent ) const
{
    bool result = false;
    auto node = m_data->m_root.get();
    if( parent.isValid() ) {
        node = static_cast< Node *>( parent.internalPointer() );
    }
    result = node->numChildren() != 0;
    return result;
}


}
