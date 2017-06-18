
#include "AbstractTemplateProvider.h"


namespace Quartz { namespace Plugin { namespace Creator {

const QString AbstractTemplateProvider::PLUGIN_TYPE{ "qz.template" };

AbstractTemplateProvider::AbstractTemplateProvider(
        const QString &pluginID,
        const QString &pluginName )
    : AbstractPlugin{ pluginID, pluginName, PLUGIN_TYPE }
{

}

AbstractTemplateProvider::~AbstractTemplateProvider()
{

}

} } }
