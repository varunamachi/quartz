
#include "AbstractPageProvider.h"

namespace Quartz {

const QString AbstractPageProvider::PLUGIN_TYPE{ "quartz.page" };

AbstractPageProvider::AbstractPageProvider(
        const QString &pluginId,
        const QString &pluginName,
        const QStringList &dependencies )
    : AbstractPlugin{ pluginId, pluginName, PLUGIN_TYPE, dependencies }
{

}

}
