
#include "AbstractPageProvider.h"

namespace Quartz {

const QString AbstractPageProvider::PLUGIN_TYPE{ "qz.page" };

AbstractPageProvider::AbstractPageProvider(
        const QString &pluginId,
        const QString &pluginName )
    : AbstractPlugin{ pluginId, pluginName, PLUGIN_TYPE }
{

}

}
