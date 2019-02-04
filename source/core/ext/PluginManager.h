#pragma once

#include <memory>

#include <QVector>

#include "../QuartzCore.h"
#include "../utils/Macros.h"

class QDir;
class QString;
class QFileInfo;
class QLibrary;

namespace Quartz { namespace Ext {

class Extension;
class Plugin;
QZ_INTERFACE IExtensionAdapter;

class QUARTZ_CORE_API PluginManager
{
public:
    QZ_NO_COPY(PluginManager);

    PluginManager();

    ~PluginManager();

    bool loadFrom(const QString &location);

    bool destroy();

    void registerPluginAdapter(std::shared_ptr<IExtensionAdapter> adapter);

    void registerPluginAdapter(IExtensionAdapter *adapter);

    QVector< const Plugin *> plugins() const;

    const Plugin * plugin(const QString &pluginId) const;

    const QLibrary * libraryForPlugin(const QString &pluginId) const;

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;

};

} }
