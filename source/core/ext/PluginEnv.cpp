#include <QString>

#include "PluginEnv.h"

namespace Quartz { namespace Ext {

struct PluginEnv::Data
{
    Data(const QString &pluginPath,
          const QString &pluginLibName,
          const QString &platformVersion)
        : m_pluginPath(pluginPath)
        , m_pluginLibName(pluginLibName)
        , m_platformVersion(platformVersion)
    {

    }

    const QString m_pluginPath;

    const QString m_pluginLibName;

    const QString m_platformVersion;
};

PluginEnv::PluginEnv(const QString &pluginPath,
                      const QString &pluginLibName,
                      const QString &platformVersion)
    : m_data(std::make_unique<Data>(pluginPath, pluginLibName, platformVersion))
{

}

PluginEnv::~PluginEnv()
{

}

const QString &PluginEnv::pluginPath() const
{
    return m_data->m_pluginPath;
}

const QString &PluginEnv::pluginLibName() const
{
    return m_data->m_pluginLibName;
}

const QString &PluginEnv::platformVersion() const
{
    return m_data->m_platformVersion;
}

} }
