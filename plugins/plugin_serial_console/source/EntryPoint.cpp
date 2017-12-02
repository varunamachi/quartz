
#include <core/ext/PluginEnv.h>
#include <core/ext/Plugin.h>

#include <base/QzAppContext.h>

#include <plugin_base/PluginContext.h>

#include "SerialConsolePlugin.h"

void initResource() {
    Q_INIT_RESOURCE( serial_console );
}

extern "C" {

Q_DECL_EXPORT PluginWrapper getPluginWrapper(
        PluginInputWrapper *input )
{
    initResource();
    auto plugin =
        std::unique_ptr< Quartz::Ext::SerialConsole::SerialConsolePlugin >{
            new Quartz::Ext::SerialConsole::SerialConsolePlugin{} };
    auto pluginPtr = plugin.get();
    Quartz::Ext::PluginContext::init(
                std::move( plugin ),
                std::move( input->env ),
                dynamic_cast< Quartz::QzAppContext *>( input->appContext ));
    return PluginWrapper{ pluginPtr };
}

Q_DECL_EXPORT void destroy()
{
    Quartz::Ext::PluginContext::destroy();
}

}
