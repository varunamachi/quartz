#pragma once

#include <memory>

#include <QString>
#include <QVector>

namespace Quartz {
class Node;
using NodePtr = std::shared_ptr< Node >;
using NodeCountType = QVector< Node >::size_type;

class Node
{
public:
    explicit Node( const QString &nodeId );

    ~Node();

    const QString & nodeId() const;

    const QVector< NodePtr > & children() const;

    QVector< NodePtr > & children();

    NodeCountType numChildren() const;

    const Node * nodeAt( NodeCountType index ) const;

    Node * nodeAt( NodeCountType index );

    void addChild( NodePtr node );

    bool removeChild( const QString &nodeId );

private:
    struct Data;
    std::unique_ptr< Data > m_data;
    inline Data * d()
    {
        return m_data.get();
    }

};


}
