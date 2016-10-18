
#include "Node.h"


namespace Quartz {

struct Node::Data
{
    Data( const QString id )
        : m_id( id )
    {

    }

    QString m_id;

    QVector< NodePtr > m_children;

};

Node::Node( const QString &nodeId )
//    : m_data( std::make_unique< Data >( nodeId ))
    : m_data( new Data{ nodeId })
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

const Node * Node::nodeAt( NodeCountType index ) const
{
    if( m_data->m_children.size() > index ) {
        return m_data->m_children.at( index ).get();
    }
    return nullptr;
}

void Node::addChild( NodePtr node )
{
    if( node ) {
        m_data->m_children.push_back( node );
    }
}

bool Node::removeChild( const QString &nodeId )
{
    bool result = false;
    int index = 0;
    for( ; m_data->m_children.size(); ++ index ) {
        if( m_data->m_children.at( index )->nodeId() == nodeId ) {
            break;
        }
    }
    if( index < m_data->m_children.size() ) {
        m_data->m_children.remove( index );
        result = true;
    }
    return result;
}




}
