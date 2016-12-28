
#include "AbstractConfigPageProvider.h"

namespace Quartz {

const QString AbstractConfigPageProvider::PLUGIN_TYPE{ "qz.configNode" };

AbstractConfigPageProvider::AbstractConfigPageProvider(
        const QString &pluginId,
        const QString &pluginName )
    : AbstractPlugin{ pluginId, pluginName, PLUGIN_TYPE }
{

}

AbstractConfigPageProvider::~AbstractConfigPageProvider()
{

}

}
