
#include "PluginContext.h"

#include <core/ext/Plugin.h>
#include <core/ext/PluginEnv.h>
#include <base/QzAppContext.h>

namespace Quartz { namespace Ext {


struct PluginContext::Data {
    Data(std::unique_ptr<PluginEnv> &&env, QzAppContext *appContext)
        : m_pluginEnv(std::move(env))
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

void PluginContext::setPlugin(std::unique_ptr<Plugin> &&plugin)
{
    m_data->m_plugin = std::move(plugin);
}

void PluginContext::destroy()
{
    s_instance.release();
}

void PluginContext::init(std::unique_ptr<PluginEnv> env,
                         QzAppContext *appCtx)
{
    //make_unique does not work here because the constructor is private
    s_instance = std::unique_ptr<PluginContext>(
                new PluginContext(std::move(env), appCtx));
}

PluginContext *PluginContext::instance()
{
    return s_instance.get();
}

PluginContext::PluginContext(std::unique_ptr<PluginEnv> &&env,
                             QzAppContext *appContext)
    : m_data(std::make_unique<Data>(std::move(env), appContext))
{

}


} }
