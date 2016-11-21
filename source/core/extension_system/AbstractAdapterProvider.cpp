
#include "AbstractAdapterProvider.h"

namespace Quartz {

const QString AbstractAdapterProvider::PLUGIN_TYPE{ "quartz.adapter" };

AbstractAdapterProvider::AbstractAdapterProvider(
        const QString &pluginId,
        const QString &pluginName,
        const QStringList &dependencies )
    : AbstractPlugin{ pluginId, pluginName, PLUGIN_TYPE, dependencies }
{

}

}
