
#include "AbstractMenuProvider.h"

namespace Quartz {

const QString AbstractMenuProvider::EXTENSION_TYPE{ "qz.menuitem" };

AbstractMenuProvider::AbstractMenuProvider(
        const QString &extensionId,
        const QString &extensionName)
    : Ext::Extension(extensionId, extensionName, EXTENSION_TYPE)
{

}

}
