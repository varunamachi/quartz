
#include "AbstractNodeProvider.h"

namespace Quartz {

const QString AbstractNodeProvider::PLUGIN_TYPE{ "quartz.node" };

AbstractNodeProvider::AbstractNodeProvider(
        const QString &pluginId,
        const QString &pluginName,
        const QStringList &dependencies )
    : AbstractPlugin{ pluginId, pluginName, PLUGIN_TYPE, dependencies }
{

}

AbstractNodeProvider::~AbstractNodeProvider()
{

}

}
