
#include "PluginContext.h"

#include <core/ext/Plugin.h>
#include <core/ext/PluginEnv.h>
#include <base/QzAppContext.h>

namespace Quartz { namespace Ext {


struct PluginContext::Data {
    Data(std::unique_ptr<Plugin> plugin,
          std::unique_ptr<PluginEnv> env,
          QzAppContext *appContext)
        : m_plugin(std::move(plugin))
        , m_pluginEnv(std::move(env))
        , m_appContext(appContext)
    {

    }

    std::unique_ptr<Plugin> m_plugin;

    std::unique_ptr<PluginEnv> m_pluginEnv;

    QzAppContext *m_appContext;

};

std::unique_ptr<PluginContext> PluginContext::s_instance(nullptr);

PluginContext::~PluginContext()
{
    m_data->m_plugin = nullptr;
    m_data->m_pluginEnv.reset();
    m_data->m_appContext = nullptr;
}


QzAppContext * PluginContext::appContext() const
{
    return m_data->m_appContext;
}

Plugin * PluginContext::plugin() const
{
    return m_data->m_plugin.get();
}

void PluginContext::destroy()
{
    s_instance.release();
}

void PluginContext::init(std::unique_ptr<Plugin> plugin,
                          std::unique_ptr<PluginEnv> env,
                          QzAppContext *appContext)
{
    s_instance = std::unique_ptr<PluginContext>{
            new PluginContext{ std::move(plugin),
                               std::move(env),
                               appContext }};
}

PluginContext *PluginContext::instance()
{
    return s_instance.get();
}

PluginContext::PluginContext(std::unique_ptr<Plugin> plugin,
                              std::unique_ptr<PluginEnv> env,
                              QzAppContext *appContext)
    : m_data{ new Data{ std::move(plugin),
                        std::move(env),
                        appContext }}
{

}


} }
