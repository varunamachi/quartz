#pragma once

#include <memory>

#include <QList>

#include "../utils/Macros.h"

class QDir;
class QString;



namespace Quartz {

QZ_INTERFACE AbstractPlugin;
QZ_INTERFACE IPluginAdapter;

class PluginManager
{
public:
    QZ_NO_COPY( PluginManager );

    PluginManager();

    ~PluginManager();


    bool loadFrom( const QString &location );

    bool destroy();

    AbstractPlugin * plugin( const QString &id ) const;

    IPluginAdapter * adapter( const QString &id ) const;

    void registerPluginAdapter( std::shared_ptr< IPluginAdapter > pluginHost );

private:
    std::size_t loadPluginAt( const QDir &dir );

    bool initializePlugin( AbstractPlugin *plugin,
                           QZ_IN_OUT QSet< QString > &loadedPluginIds );

    class Data;
    std::unique_ptr< Data > m_data;

};

}
