#include <QHash>

#include <core/logger/Logging.h>

#include "Node.h"


namespace Quartz {

struct Node::Data
{
    Data(Node *parent,
          const QString &nodeName,
          const QString &id,
          QIcon &&icon)
        : m_parent(parent)
        , m_id(id)
        , m_nodeName(nodeName)
        , m_icon(std::move(icon))
    {

    }

    Node *m_parent;

    QString m_id;

    QString m_nodeName;

    QIcon m_icon;

    QVector<NodePtr> m_children;

    QHash< QString, Node *> m_idToChild;

};

Node::Node(Node *parent,
            const QString &nodeName,
            const QString &nodeId,
            QIcon icon)
//    : m_data(std::make_unique<Data>(parent, nodeId, std::move(icon))
    : m_data(std::make_unique<Data>(parent, nodeName, nodeId, std::move(icon)))
{

}

//Node::Node(const QString &nodeId,
//            const QString &nodeName,
//            QIcon icon)
////    : m_data(std::make_unique<Data>(parent, nodeId, std::move(icon))
//    : m_data(std::make_unique<Data>(nullptr, nodeId, nodeName, std::move(icon)))
//{

//}

Node::~Node()
{

}

const QString & Node::nodeId() const
{
    return m_data->m_id;
}

const QString &Node::nodeName() const
{
    return m_data->m_nodeName;
}

const QVector<NodePtr> & Node::children() const
{
    return m_data->m_children;
}

QVector<NodePtr> & Node::children()
{
    return m_data->m_children;
}

NodeCountType Node::numChildren() const
{
    return m_data->m_children.size();
}

const Node * Node::childAt(NodeCountType index) const
{
    if (m_data->m_children.size() > index) {
        return m_data->m_children.at(index).get();
    }
    return nullptr;
}

Node *Node::childAt(NodeCountType index)
{
    if (m_data->m_children.size() > index) {
        return m_data->m_children.at(index).get();
    }
    return nullptr;
}

void Node::addChild(NodePtr node)
{
    if (node && ! hasChild(node->nodeName())) {
        m_data->m_children.push_back(node);
        m_data->m_idToChild.insert(node->nodeName(), node.get());
    }
    else if (node) {
        QZ_ERROR("Base:NodeSelector")
                << "Attempt to add child with duplicate id " << node->nodeId()
                << " to node " << m_data->m_id;
    }
}

bool Node::removeChild(const QString &nodeName)
{
    auto result = false;
    int index = 0;
    for (; m_data->m_children.size(); ++ index) {
        if (m_data->m_children.at(index)->nodeId() == nodeName) {
            break;
        }
    }
    if (index < m_data->m_children.size()) {
        m_data->m_children.remove(index);
        m_data->m_idToChild.remove(nodeName);
        result = true;
    }
    return result;
}

bool Node::hasChild(const QString &nodeName) const
{
    return m_data->m_idToChild.contains(nodeName);
}

const Node * Node::child(const QString &nodeName) const
{
    const auto *node = m_data->m_idToChild.value(nodeName);
    return node;
}

Node * Node::child(const QString &nodeName)
{
    auto *node = m_data->m_idToChild.value(nodeName);
    return node;
}

int Node::indexOfChild(const Node *node)
{
    int index = -1;
    for (int i = 0; i < m_data->m_children.size(); ++ i) {
        auto child = m_data->m_children.at(i);
        if (child.get() == node) {
            index = i;
            break;
        }
    }
    return index;
}

const QIcon &Node::icon() const
{
    return m_data->m_icon;
}

Node *Node::parent() const
{
    return m_data->m_parent;
}

void Node::setParent(Node *parent)
{
    m_data->m_parent = parent;
}

}
