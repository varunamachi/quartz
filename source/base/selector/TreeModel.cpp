
#include <core/logger/Logging.h>

#include <common/iconstore/IconFontStore.h>

#include "Node.h"

#include "TreeModel.h"


namespace Quartz {

struct TreeModel::Data
{
    Data()
        : m_root{ new Node{ nullptr, "root", "Root" }}
    {

    }

    NodePtr m_root;
};

const QString TreeModel::ADAPTER_NAME{ "Node Tree" };

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

Node *TreeModel::traverse( Node *node,
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

TreeModel::TreeModel( QObject *parent )
//    : m_data( std::make_unique< Data >() )
    : QAbstractItemModel( parent )
    , m_data( new Data{} )
{

}

TreeModel::~TreeModel()
{

}

Node * TreeModel::addNode( const QStringList &parentPath,
                           const QString &nodeName,
                           const QString &nodeId,
                           QIcon icon )
{
    QString id = nodeId.isEmpty() ? makeNodeId( parentPath, nodeName )
                                  : nodeId;
    auto node = std::make_shared< Node >( m_data->m_root.get(),
                                          nodeName,
                                          id,
                                          icon );
    if( addNode( parentPath, node )) {
        return node.get();
    }
    return nullptr;
}

bool TreeModel::addNode( const QStringList &parentPath,
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

Node * TreeModel::createPath( Node *node,
                              const QStringList &path,
                              int depth )
{
    Node *result = nullptr;
    auto child = node->child( path[ depth ]); //pathID
    if( child == nullptr ) {
        auto childId = makeNodeId( path, path[ depth ], depth );
        auto newChild = std::make_shared< Node >( node, path[ depth ], childId);
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

bool TreeModel::removeNode( const QStringList &path )
{
    auto result = false;
    auto *parent = traverse( m_data->m_root.get(), path, true, 0 );
    if( parent != nullptr ) {
        parent->removeChild( path.last() );
        result = true;
    }
    return result;
}

bool TreeModel::selectNode( const QStringList &path ) const
{
    bool result = false;
    auto sel = this->node( path );
    if( sel != nullptr ) {
        sel->nodeId();
        result = true;
    }
    return result;
}

const Node *TreeModel::node( const QStringList &path ) const
{
    Node *theNode = traverse( m_data->m_root.get(), path, false, 0 );
    return theNode;
}

QModelIndex TreeModel::index( int row,
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

QModelIndex TreeModel::parent( const QModelIndex &childIndex ) const
{
    if( ! childIndex.isValid() ) {
        return QModelIndex();
    }
    QModelIndex parentIndex{ };
    auto child = static_cast< Node * >( childIndex.internalPointer() );
    if( child != nullptr ) {
        auto parent = child->parent();
        if( parent != m_data->m_root.get() ) {
            auto gprnt = parent->parent();
            parentIndex = createIndex( gprnt->indexOfChild( parent ),
                                       0,
                                       parent );
        }
    }
    return parentIndex;
}

int TreeModel::rowCount( const QModelIndex &parent ) const
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

int TreeModel::columnCount( const QModelIndex &/*parent*/ ) const
{
    return 1;
}

QVariant TreeModel::data( const QModelIndex &index, int role ) const
{
    QVariant data { };
    if( index.isValid() ) {
        auto node = static_cast<Node *>( index.internalPointer() );
        if( role == Qt::DisplayRole ) {
            data = node->nodeName();
        } else if (role == Qt::DecorationRole) {
            auto ic = node->icon();
            if (ic.isNull()) {
                data = getIcon(MatIcon::Folder);
            } else {
                data = ic;
            }
        } else if (role == Qt::UserRole) {
            data = node->nodeId();
        }
    }
    return data;
}

bool TreeModel::hasChildren( const QModelIndex &parent ) const
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
