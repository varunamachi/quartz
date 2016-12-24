#pragma once

#include <QIcon>

#include <core/extension_system/AbstractPlugin.h>

#include "../QuartzBase.h"



namespace Quartz {

class AbstractSelector;
class Node;
using NodePtr = std::shared_ptr< Node >;

struct NodeInfo
{
    NodeInfo( const QString &nodeId,
              const QString &nodeName,
              const QStringList &nodePath,
              const QIcon &icon )
        : m_nodeId( nodeId )
        , m_nodeName( nodeName )
        , m_nodePath( nodePath )
        , m_nodeIcon( icon )
    {

    }

    QString m_nodeId;

    QString m_nodeName;

    QStringList m_nodePath;

    QIcon m_nodeIcon;
};

class QUARTZ_BASE_API AbstractGeneralNodeProvider : public AbstractPlugin
{
public:
    AbstractGeneralNodeProvider( const QString &pluginId,
                          const QString &pluginName,
                          const QStringList &dependencies );

    ~AbstractGeneralNodeProvider();

    virtual QVector< std::shared_ptr< NodeInfo >> nodes() const = 0;

    static const QString PLUGIN_TYPE;

private:
};

}
