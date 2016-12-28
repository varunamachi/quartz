
#include "AbstractAdapterProvider.h"

namespace Quartz {

const QString AbstractAdapterProvider::PLUGIN_TYPE{ "qz.adapter" };

AbstractAdapterProvider::AbstractAdapterProvider(
        const QString &pluginId,
        const QString &pluginName )
    : AbstractPlugin{ pluginId, pluginName, PLUGIN_TYPE }
{

}

}
