
#include "AbstractViewProvider.h"

namespace Quartz {

const QString AbstractViewProvider::EXTENSION_TYPE{ "qz.view" };

AbstractViewProvider::AbstractViewProvider(
        const QString &extensionId,
        const QString &extensionName )
    : Ext::Extension{ extensionId, extensionName, EXTENSION_TYPE }
{

}

}
