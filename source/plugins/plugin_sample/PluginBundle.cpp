#include <base/QzAppContext.h>

#include "Sample.h"
#include "ViewProvider.h"
#include "ContentProvider.h"
#include "NodeProvider.h"
#include "TitleItemProvider.h"
#include "PluginBundle.h"

namespace Quartz { namespace Plugin { namespace Sample {

const QString PluginBundle::BUNDLE_ID{ "qzplugin.sample" };
const QString PluginBundle::BUNDLE_NAME{ "Sample Bundle" };

PluginList PluginBundle::plugins() const
{
    QVector< std::shared_ptr< AbstractPlugin >> plugins;
    plugins.push_back( std::make_shared< ViewProvider >() );
    plugins.push_back( std::make_shared< ContentProvider >() );
    plugins.push_back( std::make_shared< NodeProvider >() );
    plugins.push_back( std::make_shared< TitleItemProvider >() );
    return plugins;
}

PluginBundle::~PluginBundle()
{

}

PluginBundle::PluginBundle()
    : Quartz::AbstractPluginBundle{ BUNDLE_ID, BUNDLE_NAME }
{

}

} } }
