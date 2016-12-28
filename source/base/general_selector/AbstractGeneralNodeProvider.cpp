
#include "AbstractGeneralNodeProvider.h"

namespace Quartz {

const QString AbstractGeneralNodeProvider::PLUGIN_TYPE{ "qz.node" };

AbstractGeneralNodeProvider::AbstractGeneralNodeProvider(
        const QString &pluginId,
        const QString &pluginName )
    : AbstractPlugin{ pluginId, pluginName, PLUGIN_TYPE }
{

}

AbstractGeneralNodeProvider::~AbstractGeneralNodeProvider()
{

}

}
