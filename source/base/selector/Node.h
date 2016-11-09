#pragma once

#include <memory>

#include <QString>
#include <QVector>
#include <QIcon>

#include "../QuartzBase.h"

namespace Quartz {
class Node;
using NodePtr = std::shared_ptr< Node >;
using NodeCountType = QVector< Node >::size_type;

class QUARTZ_BASE_API Node
{
public:
    explicit Node( Node *parent,
                   const QString &nodeId,
                   QIcon icon = QIcon{ } );

    explicit Node( const QString &nodeId,
                   QIcon icon = QIcon{ } );

    ~Node();

    const QString & nodeId() const;

    const QVector< NodePtr > & children() const;

    QVector< NodePtr > & children();

    NodeCountType numChildren() const;

    const Node * childAt( NodeCountType index ) const;

    Node * childAt( NodeCountType index );

    void addChild( NodePtr node );

    bool removeChild( const QString &nodeId );

    bool hasChild( const QString &nodeId ) const;

    const Node * child( const QString &nodeId ) const;

    Node * child( const QString &nodeId );

    int indexOfChild( const Node *node );

    const QIcon & icon() const;

    Node *parent() const;

    void setParent( Node *parent );

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};


}
