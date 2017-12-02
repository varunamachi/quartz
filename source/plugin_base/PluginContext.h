#pragma once

#include <memory>

#include <base/QzAppContext.h>

class QString;

namespace Quartz {

class QzAppContext;
class ConfigManager;
namespace Logger { class Logger; }

namespace Ext {

class Plugin;
class PluginEnv;

class PluginContext
{
public:
    ~PluginContext();

    QzAppContext * appContext() const;

    Plugin * plugin() const;

    PluginEnv * env() const;

    static void destroy();

    static void init( std::unique_ptr< Plugin > plugin,
                      std::unique_ptr< PluginEnv > env,
                      QzAppContext *appContext );

    static PluginContext * instance();

private:
    struct Data;
    std::unique_ptr< Data > m_data;

    static std::unique_ptr< PluginContext > s_instance;

    PluginContext( std::unique_ptr< Plugin > plugin,
                   std::unique_ptr< PluginEnv > env,
                   QzAppContext *appContext );
};

} }


inline Quartz::Ext::PluginContext * pluginContext()
{
    return Quartz::Ext::PluginContext::instance();
}

inline Quartz::QzAppContext * appContext()
{
    return Quartz::Ext::PluginContext::instance()->appContext();
}

inline Quartz::Ext::PluginEnv * pluginEnv()
{
    return Quartz::Ext::PluginContext::instance()->env();
}

inline Quartz::Ext::Plugin * plugin()
{
    return pluginContext()->plugin();
}

inline Quartz::ConfigManager * confman()
{
    return pluginContext()->appContext()->configManager();
}
