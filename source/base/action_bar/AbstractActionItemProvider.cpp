
#include "AbstractActionItemProvider.h"

namespace Quartz {

const QString AbstractActionItemProvider::EXTENSION_TYPE{ "qz.action_item" };

AbstractActionItemProvider::AbstractActionItemProvider(
        const QString &extensionId,
        const QString &extensionName)
    : Ext::Extension(extensionId, extensionName, EXTENSION_TYPE)
{

}

}
