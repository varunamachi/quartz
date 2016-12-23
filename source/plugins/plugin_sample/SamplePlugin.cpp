
#include <core/extension_system/BundleEnv.h>

#include <base/QzAppContext.h>

#include <plugin_base/BundleContext.h>

#include "PluginBundle.h"

extern "C" {

Q_DECL_EXPORT PluginBundleWrapper getBundleWrapper(
        BundleInputWrapper *input )
{
    auto bundle = std::unique_ptr< Quartz::Plugin::Sample::PluginBundle >{
            new Quartz::Plugin::Sample::PluginBundle{} };
    auto bundlePtr = bundle.get();
    Quartz::Plugin::BundleContext::init(
                std::move( bundle ),
                std::move( input->env ),
                dynamic_cast< Quartz::QzAppContext *>( input->appContext ));
//    return new PluginBundleWrapper{ };
    return PluginBundleWrapper{ bundlePtr };
}

Q_DECL_EXPORT void destroy()
{
    Quartz::Plugin::BundleContext::destroy();
}

}
