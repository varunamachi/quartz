
#include "AbstractPageProvider.h"

namespace Quartz {

const QString AbstractPageProvider::EXTENSION_TYPE{ "qz.page" };

AbstractPageProvider::AbstractPageProvider(
        const QString &extensionId,
        const QString &extensionName)
    : Ext::Extension(extensionId, extensionName, EXTENSION_TYPE)
{

}

}
