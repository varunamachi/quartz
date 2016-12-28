
#include "AbstractActionItemProvider.h"

namespace Quartz {

const QString AbstractActionItemProvider::PLUGIN_TYPE{ "qz.action_item" };

AbstractActionItemProvider::AbstractActionItemProvider(
        const QString &pluginId,
        const QString &pluginName )
    : AbstractPlugin{ pluginId, pluginName, PLUGIN_TYPE }
{

}

}
