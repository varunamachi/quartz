
#include "AbstractGeneralNodeProvider.h"

namespace Quartz {

const QString AbstractGeneralNodeProvider::PLUGIN_TYPE{ "qz.node" };

AbstractGeneralNodeProvider::AbstractGeneralNodeProvider(
        const QString &pluginId,
        const QString &pluginName,
        const QStringList &dependencies )
    : AbstractPlugin{ pluginId, pluginName, PLUGIN_TYPE, dependencies }
{

}

AbstractGeneralNodeProvider::~AbstractGeneralNodeProvider()
{

}

}
