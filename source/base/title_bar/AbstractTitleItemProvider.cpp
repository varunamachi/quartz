
#include "AbstractTitleItemProvider.h"

namespace Quartz {

const QString AbstractTitleItemProvider::PLUGIN_TYPE{ "qz.title_item" };

AbstractTitleItemProvider::AbstractTitleItemProvider(
        const QString &pluginId,
        const QString &pluginName )
    : AbstractPlugin{ pluginId, pluginName, PLUGIN_TYPE }
{

}

}
