
#include <core/logger/Logging.h>

#include "AbstractGeneralNodeProvider.h"
#include "GeneralNodeTree.h"


namespace Quartz {


GeneralNodeTree::GeneralNodeTree( QObject *parent )
    : TreeModel{ parent }
{

}

const QString &GeneralNodeTree::pluginType() const
{
    return  AbstractGeneralNodeProvider::PLUGIN_TYPE;
}

const QString &GeneralNodeTree::pluginAdapterName() const
{
    return ADAPTER_NAME;
}

bool GeneralNodeTree::handlePlugin( AbstractPlugin *plugin )
{
    bool result = true;
    auto nodeProvider = dynamic_cast< AbstractGeneralNodeProvider *>( plugin );
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

bool GeneralNodeTree::finalizePlugins()
{
    bool result = false;
    return result;
}




}
