
#include "AbstractSelectorProvider.h"

namespace Quartz {

const QString AbstractSelectorProvider::PLUGIN_TYPE{ "qz.selector" };

AbstractSelectorProvider::AbstractSelectorProvider(
        const QString &pluginId,
        const QString &pluginName )
    : AbstractPlugin{ pluginId, pluginName, PLUGIN_TYPE }
{

}

AbstractSelectorProvider::~AbstractSelectorProvider()
{

}


}
