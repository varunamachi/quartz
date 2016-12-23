#pragma once

#include <memory>

#include <QList>

#include "../QuartzCore.h"
#include "../utils/Macros.h"

class QDir;
class QString;
class QFileInfo;

namespace Quartz {

QZ_INTERFACE AbstractPlugin;
QZ_INTERFACE IPluginAdapter;

class QUARTZ_CORE_API PluginManager
{
public:
    QZ_NO_COPY( PluginManager );

    PluginManager();

    ~PluginManager();


    bool loadFrom( const QString &location );

    bool destroy();

    AbstractPlugin * plugin( const QString &id ) const;

    IPluginAdapter * adapter( const QString &id ) const;

    void registerPluginAdapter( IPluginAdapter *pluginHost );

private:
    std::size_t loadPluginAt( const QDir &pluginRoot );

    std::size_t load(
            const QString &pluginRoot,
            const QString &pluginFilePath );

    bool initializePlugin( AbstractPlugin *plugin,
                           QZ_IN_OUT QSet< QString > &loadedPluginIds );

    class Data;
    std::unique_ptr< Data > m_data;

};

}
