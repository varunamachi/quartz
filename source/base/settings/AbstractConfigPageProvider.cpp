
#include "AbstractConfigPageProvider.h"

namespace Quartz {

const QString AbstractConfigPageProvider::PLUGIN_TYPE{ "qz.configNode" };

AbstractConfigPageProvider::AbstractConfigPageProvider(
        const QString &pluginId,
        const QString &pluginName,
        const QStringList &dependencies )
    : AbstractPlugin{ pluginId, pluginName, PLUGIN_TYPE, dependencies }
{

}

AbstractConfigPageProvider::~AbstractConfigPageProvider()
{

}

}
