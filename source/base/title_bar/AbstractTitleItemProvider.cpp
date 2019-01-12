
#include "AbstractTitleItemProvider.h"

namespace Quartz {

const QString AbstractTitleItemProvider::EXTENSION_TYPE{ "qz.title_item" };

AbstractTitleItemProvider::AbstractTitleItemProvider(
        const QString &pluginId,
        const QString &pluginName)
    : Ext::Extension(pluginId, pluginName, EXTENSION_TYPE)
{

}

}
