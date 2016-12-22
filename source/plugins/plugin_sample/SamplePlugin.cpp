
#include <core/extension_system/BundleEnv.h>

#include <base/QzAppContext.h>

#include <plugin_base/BundleContext.h>

#include "PluginBundle.h"

extern "C" {

Q_DECL_EXPORT PluginBundleWrapper * getBundleWrapper()
{
//    auto bundle = std::unique_ptr< PluginBundle >{};
//    return new PluginBundleWrapper{ };
    return new PluginBundleWrapper{
        new Quartz::Plugin::Sample::PluginBundle{} };
}

Q_DECL_EXPORT void destroy()
{
    Quartz::Plugin::BundleContext::destroy();
}

}
