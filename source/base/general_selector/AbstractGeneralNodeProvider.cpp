
#include "AbstractGeneralNodeProvider.h"

namespace Quartz {

const QString AbstractGeneralNodeProvider::EXTENSION_TYPE{ "qz.node" };

AbstractGeneralNodeProvider::AbstractGeneralNodeProvider(
        const QString &extensionId,
        const QString &extensionName)
    : Ext::Extension(extensionId, extensionName, EXTENSION_TYPE)
{

}

AbstractGeneralNodeProvider::~AbstractGeneralNodeProvider()
{

}

}
