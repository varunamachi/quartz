#include <core/extension_system/AbstractPlugin.h>
#include <core/extension_system/AbstractPluginBundle.h>

#include "Sample.h"
#include "ViewProvider.h"
#include "ContentProvider.h"
#include "NodeProvider.h"
#include "TitleItemProvider.h"


extern "C" {

Q_DECL_EXPORT PluginListWrapper * getPlugins()
{
    using namespace Quartz;
    using namespace Plugin;
    QVector< std::shared_ptr< AbstractPlugin >> plugins;
    plugins.push_back( std::make_shared< Sample::ViewProvider >() );
    plugins.push_back( std::make_shared< Sample::ContentProvider >() );
    plugins.push_back( std::make_shared< Sample::NodeProvider >() );
    plugins.push_back( std::make_shared< Sample::TitleItemProvider >() );
//    return new PluginListWrapper{ plugins };

    //below code is temporary and the plugins wont be loaded
    return nullptr;

}

}
