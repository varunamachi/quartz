
#include <core/ext/PluginEnv.h>

#include <base/QzAppContext.h>

#include <plugin_base/PluginContext.h>

#include "OrekPlugin.h"

void initResource() {
    Q_INIT_RESOURCE( orek_client );
}

extern "C" {

Q_DECL_EXPORT PluginWrapper getPluginWrapper(
        PluginInputWrapper *input )
{
    initResource();
    auto plugin= std::unique_ptr< Quartz::Ext::Orek::OrekPlugin >{
            new Quartz::Ext::Orek::OrekPlugin{} };
    auto pluginPtr = plugin.get();
    Quartz::Ext::PluginContext::init(
                std::move( plugin ),
                std::move( input->env ),
                dynamic_cast< Quartz::QzAppContext *>( input->appContext ));
//    return new PluginWrapper{ };
    return PluginWrapper{ pluginPtr };
}

Q_DECL_EXPORT void destroy()
{
//    Q_CLEANUP_RESOURCE( sample );
    Quartz::Ext::PluginContext::destroy();
}

}
