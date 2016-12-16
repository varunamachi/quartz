#include <base/QzAppContext.h>

#include "Sample.h"
#include "ViewProvider.h"
#include "ContentProvider.h"
#include "NodeProvider.h"
#include "TitleItemProvider.h"
#include "PluginBundle.h"

namespace Quartz { namespace Plugin { namespace Sample {

std::unique_ptr< PluginBundle > PluginBundle::s_instance = nullptr;

PluginList PluginBundle::plugins() const
{
    QVector< std::shared_ptr< AbstractPlugin >> plugins;
    plugins.push_back( std::make_shared< ViewProvider >() );
    plugins.push_back( std::make_shared< ContentProvider >() );
    plugins.push_back( std::make_shared< NodeProvider >() );
    plugins.push_back( std::make_shared< TitleItemProvider >() );
    return plugins;
}

PluginBundle *PluginBundle::get()
{
    if( s_instance.get() == nullptr ) {
        s_instance = std::unique_ptr< PluginBundle >{ new PluginBundle{} };
    }
    return s_instance.get();
}

QzAppContext *PluginBundle::appContext()
{
    return s_instance->context< QzAppContext >();
}

void PluginBundle::destroy()
{
    s_instance.reset();
}

} } }
