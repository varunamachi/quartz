#pragma once

#include <memory>

#include "../QuartzCore.h"

class QString;

namespace Quartz { namespace Ext {

class QUARTZ_CORE_API PluginEnv
{
public:
    PluginEnv( const QString &pluginPath,
               const QString &pluginLibName,
               const QString &platformVersion );

    ~PluginEnv();

    const QString & pluginPath() const;

    const QString & pluginLibName() const;

    const QString & platformVersion() const;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

} }
