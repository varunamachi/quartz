
#include "PluginBundle.h"

extern "C" {

Q_DECL_EXPORT PluginBundleWrapper * bundleWrapper()
{
    return new PluginBundleWrapper{
        Quartz::Plugin::Sample::PluginBundle::get() };
}

Q_DECL_EXPORT void destroy()
{
    Quartz::Plugin::Sample::PluginBundle::destroy();
}

}
