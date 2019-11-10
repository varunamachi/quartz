#pragma once

#include <plugin_base/PluginContext.h>
#include <core/app_config/ConfigManager.h>

namespace Quartz { namespace Ext { namespace WebTech {

struct Conf {
    static const QString CONF_DOMAIN;
    static const QString EDITOR_THEME;
    static const QString EDITOR_VLINE_NUM;
    static const QString EDITOR_SHOW_MINIMAP;
    static const QString EDITOR_SHOW_LINENUM;
};

template <typename T>
T conf(const QString& key, const T& def = {}) {
    return confman()->get<T>(key, def, Conf::CONF_DOMAIN);
}

// template<typename T>
// void setConf(const QString &key, const T& val)
//{
//    confman()->set<T>(key, val, Conf::CONF_DOMAIN);
//}

inline void setConf(const QString& key, const QVariant& value) {
    confman()->store(key, value, Conf::CONF_DOMAIN);
}

}}} // namespace Quartz::Ext::WebTech
