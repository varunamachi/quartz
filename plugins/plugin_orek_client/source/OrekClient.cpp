
#include <core/extension_system/BundleEnv.h>

#include <base/QzAppContext.h>

#include <plugin_base/BundleContext.h>

#include "PluginBundle.h"

void initResource() {
    Q_INIT_RESOURCE( orek_client );
}

extern "C" {

Q_DECL_EXPORT PluginBundleWrapper getBundleWrapper(
        BundleInputWrapper *input )
{
    initResource();
    auto bundle = std::unique_ptr< Quartz::OrekClient::PluginBundle >{
            new Quartz::OrekClient::PluginBundle{} };
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
//    Q_CLEANUP_RESOURCE( sample );
    Quartz::Plugin::BundleContext::destroy();
}

}
