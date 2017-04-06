
#include <core/extension_system/BundleEnv.h>

#include <base/QzAppContext.h>

#include <plugin_base/BundleContext.h>

#include "PluginBundle.h"

void initResource() {
    Q_INIT_RESOURCE( serial_console );
}

extern "C" {

Q_DECL_EXPORT PluginBundleWrapper getBundleWrapper(
        BundleInputWrapper *input )
{
    initResource();
    auto bundle = 
        std::unique_ptr< Quartz::Plugin::SerialConsole::PluginBundle >{
            new Quartz::Plugin::SerialConsole::PluginBundle{} };
    auto bundlePtr = bundle.get();
    Quartz::Plugin::BundleContext::init(
                std::move( bundle ),
                std::move( input->env ),
                dynamic_cast< Quartz::QzAppContext *>( input->appContext ));
    return PluginBundleWrapper{ bundlePtr };
}

Q_DECL_EXPORT void destroy()
{
    Quartz::Plugin::BundleContext::destroy();
}

}
