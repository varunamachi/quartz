#pragma once

#include <memory>

#include <QString>
#include <QVector>
#include <QIcon>
#include <QMetaType>
#include <QVariant>

#include "../QuartzBase.h"

namespace Quartz {
class Node;
using NodePtr = std::shared_ptr<Node>;
using NodeCountType = QVector<Node>::size_type;

class QUARTZ_BASE_API Node
{
public:
    explicit Node(Node *parent,
                   const QString &nodeName,
                   const QString &nodeId,
                   QIcon icon = QIcon());

//    explicit Node(const QString &nodeId,
//                   const QString &nodeName,
//                   QIcon icon = QIcon());

    ~Node();

    const QString & nodeId() const;

    const QString & nodeName() const;

    const QVector<NodePtr> & children() const;

    QVector<NodePtr> & children();

    NodeCountType numChildren() const;

    const Node * childAt(NodeCountType index) const;

    Node * childAt(NodeCountType index);

    void addChild(NodePtr node);

    bool removeChild(const QString &nodeName);

    bool hasChild(const QString &nodeName) const;

    const Node * child(const QString &nodeName) const;

    Node * child(const QString &nodeName);

    int indexOfChild(const Node *node);

    const QIcon & icon() const;

    Node *parent() const;

    void setParent(Node *parent);

    inline static QStringList toPath(const QString &pathStr)
    {
        return pathStr.split(">");
    }

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

template<typename T> T node_cast(QVariant &var) {
    auto tn = var.value<Node *>();
    return dynamic_cast<T>(tn);
}

}

Q_DECLARE_METATYPE(Quartz::Node*)

