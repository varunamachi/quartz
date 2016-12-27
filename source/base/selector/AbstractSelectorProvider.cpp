
#include "AbstractSelectorProvider.h"

namespace Quartz {

const QString AbstractSelectorProvider::PLUGIN_TYPE{ "qz.selector" };

AbstractSelectorProvider::AbstractSelectorProvider(
        const QString &pluginId,
        const QString &pluginName,
        const QStringList &dependencies )
    : AbstractPlugin{ pluginId, pluginName, PLUGIN_TYPE, dependencies }
{

}

AbstractSelectorProvider::~AbstractSelectorProvider()
{

}


}
