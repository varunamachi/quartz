
#include <core/ext/PluginEnv.h>
#include <core/ext/Plugin.h>

#include <base/QzAppContext.h>

#include <plugin_base/PluginContext.h>

#include "Plugin.h"

void initResource() {
    Q_INIT_RESOURCE(creator);
}

extern "C" {

Q_DECL_EXPORT PluginWrapper getPluginWrapper(
        PluginInputWrapper *input)
{
    initResource();
    Quartz::Ext::PluginContext::init(
                std::move(input->env),
                dynamic_cast<Quartz::QzAppContext *>(input->appContext));
    auto plugin = std::make_unique<Quartz::Ext::Creator::Plugin>();
    auto pluginPtr = plugin.get();
    Quartz::Ext::PluginContext::instance()->setPlugin(std::move(plugin));
    return PluginWrapper{pluginPtr, true};
}

Q_DECL_EXPORT void destroy()
{
//    Q_CLEANUP_RESOURCE(sample);
    Quartz::Ext::PluginContext::destroy();
}

}
