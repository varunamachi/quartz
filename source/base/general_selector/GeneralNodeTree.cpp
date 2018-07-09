
#include <core/logger/Logging.h>

#include "AbstractGeneralNodeProvider.h"
#include "GeneralNodeTree.h"


namespace Quartz {


GeneralNodeTree::GeneralNodeTree( QObject *parent )
    : TreeModel{ parent }
{

}

const QString &GeneralNodeTree::extensionType() const
{
    return  AbstractGeneralNodeProvider::EXTENSION_TYPE;
}

const QString &GeneralNodeTree::extensionAdapterName() const
{
    return ADAPTER_NAME;
}

bool GeneralNodeTree::handleExtension( Ext::Extension *extension )
{
    bool result = true;
    auto nodeProvider = dynamic_cast< AbstractGeneralNodeProvider *>(
                extension );
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
        auto extensionName = extension != nullptr ? extension->extensionId()
                                            : "<null>";
        QZ_ERROR( "Qz:NodeSelector" )
                << "Invalid node extension provided: " << extensionName;
    }
    return result;
}

bool GeneralNodeTree::finalizeExtension()
{
    bool result = false;
    return result;
}




}
