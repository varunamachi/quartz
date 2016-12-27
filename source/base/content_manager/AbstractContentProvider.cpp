
#include "AbstractContentProvider.h"

namespace Quartz {

const QString AbstractContentProvider::PLUGIN_TYPE{ "qz.content" };


AbstractContentProvider::AbstractContentProvider(
        const QString &pluginId,
        const QString &pluginName,
        const QStringList &dependencies )
    : AbstractPlugin{ pluginId, pluginName, PLUGIN_TYPE, dependencies }
{

}


AbstractContentProvider::~AbstractContentProvider()
{

}



}
