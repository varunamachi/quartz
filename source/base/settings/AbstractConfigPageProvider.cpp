
#include "AbstractConfigPageProvider.h"

namespace Quartz {

const QString AbstractConfigPageProvider::EXTENSION_TYPE{ "qz.configNode" };

AbstractConfigPageProvider::AbstractConfigPageProvider(
        const QString &extensionId,
        const QString &extensionName)
    : Ext::Extension(extensionId, extensionName, EXTENSION_TYPE)
{

}

AbstractConfigPageProvider::~AbstractConfigPageProvider()
{

}

}
