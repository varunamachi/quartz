#pragma once

#include <QIcon>

#include <core/ext/Extension.h>

#include "../QuartzBase.h"



namespace Quartz {

class AbstractSelector;
class Node;
using NodePtr = std::shared_ptr<Node>;

struct NodeInfo
{
    NodeInfo(const QStringList &nodePath,
              const QString &nodeName,
              const QString &nodeId,
              const QIcon &icon)
        : m_nodePath(nodePath)
        , m_nodeName(nodeName)
        , m_nodeId(nodeId)
        , m_nodeIcon(icon)
    {

    }

    QStringList m_nodePath;

    QString m_nodeName;

    QString m_nodeId;

    QIcon m_nodeIcon;
};

class QUARTZ_BASE_API AbstractGeneralNodeProvider : public Ext::Extension
{
public:
    AbstractGeneralNodeProvider(const QString &extensionId,
                                 const QString &extensionName);

    ~AbstractGeneralNodeProvider();

    virtual QVector<std::shared_ptr<NodeInfo>> nodes() const = 0;

    static const QString EXTENSION_TYPE;

private:
};

}
