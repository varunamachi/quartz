
#include <core/logger/Logging.h>

#include "AbstractConfigNodeProvider.h"
#include "ConfigNodeTree.h"


namespace Quartz {


ConfigNodeTree::ConfigNodeTree( QObject *parent )
    : TreeModel{ parent }
{

}

const QString &ConfigNodeTree::pluginType() const
{
    return  AbstractConfigNodeProvider::PLUGIN_TYPE;
}

const QString &ConfigNodeTree::pluginAdapterName() const
{
    return ADAPTER_NAME;
}

bool ConfigNodeTree::handlePlugin( AbstractPlugin *plugin )
{
    bool result = true;
    auto nodeProvider = dynamic_cast< AbstractConfigNodeProvider *>( plugin );
    if( nodeProvider != nullptr ) {
       auto nodes = nodeProvider->nodes();
       foreach( auto nodeInfo, nodes ) {
           auto res = addNode( nodeInfo->m_nodePath,
                               nodeInfo->m_nodeName,
                               nodeInfo->m_nodeId,
                               nodeInfo->m_nodeIcon );
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

bool ConfigNodeTree::finalizePlugins()
{
    bool result = false;
    return result;
}




}
