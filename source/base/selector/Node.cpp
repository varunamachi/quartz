#include <QHash>

#include <core/logger/Logger.h>

#include "Node.h"


namespace Quartz {

struct Node::Data
{
    Data( Node *parent,
          const QString id,
          QIcon &&icon )
        : m_parent( parent )
        , m_id( id )
        , m_icon( std::move( icon ))
    {

    }

    Node *m_parent;

    QString m_id;

    QIcon m_icon;

    QVector< NodePtr > m_children;

    QHash< QString, Node *> m_idToChild;

};

Node::Node( Node *parent,
            const QString &nodeId,
            QIcon icon )
//    : m_data( std::make_unique< Data >( parent, nodeId, std::move( icon ))
    : m_data( new Data{ parent, nodeId, std::move( icon ) })
{

}

Node::~Node()
{

}

const QString & Node::nodeId() const
{
    return m_data->m_id;
}

const QVector< NodePtr > & Node::children() const
{
    return m_data->m_children;
}

QVector< NodePtr > & Node::children()
{
    return m_data->m_children;
}

NodeCountType Node::numChildren() const
{
    return m_data->m_children.size();
}

const Node * Node::childAt( NodeCountType index ) const
{
    if( m_data->m_children.size() > index ) {
        return m_data->m_children.at( index ).get();
    }
    return nullptr;
}

Node *Node::childAt(NodeCountType index)
{
    if( m_data->m_children.size() > index ) {
        return m_data->m_children.at( index ).get();
    }
    return nullptr;
}

void Node::addChild( NodePtr node )
{
    if( node && ! hasChild( node->nodeId() )) {
        m_data->m_children.push_back( node );
        m_data->m_idToChild.insert( node->nodeId(), node.get() );
    }
    else if( node ) {
        QZ_ERROR( "Base:NodeSelector" )
                << "Attempt to add child with duplicate id " << node->nodeId()
                << " to node " << m_data->m_id;
    }
}

bool Node::removeChild( const QString &nodeId )
{
    auto result = false;
    int index = 0;
    for( ; m_data->m_children.size(); ++ index ) {
        if( m_data->m_children.at( index )->nodeId() == nodeId ) {
            break;
        }
    }
    if( index < m_data->m_children.size() ) {
        m_data->m_children.remove( index );
        m_data->m_idToChild.remove( nodeId );
        result = true;
    }
    return result;
}

bool Node::hasChild( const QString &nodeId ) const
{
    return m_data->m_idToChild.contains( nodeId );
}

const Node * Node::child( const QString &nodeId ) const
{
    const auto *node = m_data->m_idToChild.value( nodeId );
    return node;
}

Node * Node::child( const QString &nodeId )
{
    auto *node = m_data->m_idToChild.value( nodeId );
    return node;
}

const QIcon &Node::icon() const
{
    return m_data->m_icon;
}

Node *Node::parent() const
{
    return m_data->m_parent;
}


}
