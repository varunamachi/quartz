
#include "AbstractContentProvider.h"

namespace Quartz {

const QString AbstractContentProvider::PLUGIN_TYPE{ "qz.content" };


AbstractContentProvider::AbstractContentProvider(
        const QString &pluginId,
        const QString &pluginName )
    : AbstractPlugin{ pluginId, pluginName, PLUGIN_TYPE }
{

}


AbstractContentProvider::~AbstractContentProvider()
{

}



}
