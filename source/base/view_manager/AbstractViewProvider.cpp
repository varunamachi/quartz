
#include "AbstractViewProvider.h"

namespace Quartz {

const QString AbstractViewProvider::PLUGIN_TYPE{ "qz.view" };

AbstractViewProvider::AbstractViewProvider(
        const QString &pluginId,
        const QString &pluginName )
    : AbstractPlugin{ pluginId, pluginName, PLUGIN_TYPE }
{

}

}
