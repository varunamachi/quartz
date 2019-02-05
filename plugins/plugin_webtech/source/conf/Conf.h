#pragma once

#include <plugin_base/PluginContext.h>
#include <core/app_config/ConfigManager.h>

namespace Quartz { namespace Ext { namespace WebTech {

struct Conf
{
    static const QString DOMAIN;
    static const QString EDITOR_THEME;
    static const QString EDITOR_SHOW_VLINE;
    static const QString EDITOR_SHOW_MINIMAP;
    static const QString EDITOR_SHOW_LINENUM;
};


template<typename T>
T conf(const QString &key, const T& def = {})
{
    return confman()->get<T>(key, def, Conf::DOMAIN);
}

template<typename T>
T setConf(const QString &key, const T& val)
{
    return confman()->set<T>(key, val, Conf::DOMAIN);
}


} } }

