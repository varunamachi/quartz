
#include "AbstractConfigNodeProvider.h"

namespace Quartz {

const QString AbstractConfigNodeProvider::PLUGIN_TYPE{ "quartz.configNode" };

AbstractConfigNodeProvider::AbstractConfigNodeProvider(
        const QString &pluginId,
        const QString &pluginName,
        const QStringList &dependencies )
    : AbstractPlugin{ pluginId, pluginName, PLUGIN_TYPE, dependencies }
{

}

AbstractConfigNodeProvider::~AbstractConfigNodeProvider()
{

}

}
