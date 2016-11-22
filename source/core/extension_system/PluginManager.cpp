#include <memory>

#include <QHash>
#include <QDir>
#include <QLibrary>
#include <QSet>
#include <QDebug>

#include "../logger/Logging.h"
#include "AbstractPlugin.h"
#include "IPluginAdapter.h"
#include "PluginManager.h"
#include "AbstractAdapterProvider.h"

namespace Quartz {

using PluginMap = QHash< QString, std::shared_ptr< AbstractPlugin >>;
using AdapterMap = QHash< QString, IPluginAdapter *>;
using LibraryList = QList< std::shared_ptr< QLibrary >>;


typedef PluginListWrapper * ( *PluginFunc )();
static const char * PLUGIN_FUNC_NAME = "getPlugins";

class PluginManager::Data
{

public:
    Data()
        : m_active( true )
    {

    }

    PluginMap & plugins()
    {
        return m_plugins;
    }

    const PluginMap & plugins() const
    {
        return m_plugins;
    }

    AdapterMap & adapters()
    {
        return m_adapters;
    }

    const AdapterMap & adapters() const
    {
        return m_adapters;
    }

    LibraryList & libraries()
    {
        return m_libraries;
    }

    const LibraryList & libraries() const
    {
        return m_libraries;
    }

    void setActive( bool value )
    {
        m_active = value;
    }

    bool isActive() const
    {
        return m_active;
    }

private:
    PluginMap m_plugins;

    AdapterMap m_adapters;

    LibraryList m_libraries;

    bool m_active;
};


PluginManager::PluginManager()
//    : m_data( std::make_unique< PluginManager::Data >() )
    : m_data( std::unique_ptr< Data >( new Data() ))
{

}


PluginManager::~PluginManager()
{
    destroy();
}


bool PluginManager::loadFrom( const QString &location )
{
    bool result = true;
    QDir dir{ location };
    auto dirList = dir.entryInfoList( QDir::Dirs | QDir::NoDotAndDotDot,
                                      QDir::SortFlag::NoSort );

    foreach(const QFileInfo &info, dirList) {
        if( info.isReadable() ) {
            QDir pluginDir{ info.absoluteFilePath() };
            auto numLoaded = loadPluginAt( pluginDir );
            QZ_DEBUG( "Qz:Core:Ext" )
                    << "Loaded " << numLoaded << " plugins from "
                    << info.absoluteFilePath();
        }
        else {
            QZ_WARN( "Qz:Core:Ext" ) << "Could not read plugin directory at "
                                     << info.absoluteFilePath();
        }
    }
    QZ_INFO( "Qz:Core:Ext" ) << "Initilizing " << m_data->plugins().size()
                             << "plugins from " << location;
    if( ! m_data->plugins().isEmpty() ) {
        QSet< QString > loaded;
        for( auto pit = m_data->plugins().begin();
             pit != m_data->plugins().end();
             ++ pit ) {
            auto &plugin = pit.value();
            if( ! loaded.contains( plugin->pluginId() )) {
                initializePlugin( plugin.get(), loaded );
            }
        }
    }
    else {
        QZ_WARN( "Qz:Core:Ext" ) << "No plugins loaded from " << location;
    }
    return result;
}


bool PluginManager::destroy()
{
    if( ! m_data->isActive() ) {
        return false;
    }
    bool result = true;
    for( auto it = m_data->adapters().begin();
         it != m_data->adapters().end();
         ++ it ) {
        auto &handler = it.value();
        result = result && handler->finalizePlugins();
    }
    foreach( auto &lib, m_data->libraries() ) {
        result = result && lib->unload();
    }
    m_data->setActive( false );
    return result;
}


AbstractPlugin * PluginManager::plugin( const QString &id ) const
{
    auto &plugin = m_data->plugins().value( id );
    return plugin.get();
}


IPluginAdapter * PluginManager::adapter( const QString &id ) const
{
    return m_data->adapters().value( id );
}


void PluginManager::registerPluginAdapter(
        IPluginAdapter *pluginAdapter )
{
    if( ! m_data->adapters().contains( pluginAdapter->pluginType() )) {
        m_data->adapters().insert( pluginAdapter->pluginType(), pluginAdapter );
    }
}

bool PluginManager::initializePlugin( AbstractPlugin *plugin,
                                      QSet< QString > &loadedPluginIds )
{

    //How to handle cyclic dependency?
    if( plugin == nullptr ) {
        return false;
    }
    bool result = true;
    auto &dependencies = plugin->dependencies();
    foreach( auto &dpId, dependencies ) {
        if( loadedPluginIds.contains( dpId )) {
            //debug log, may be
            continue;
        }
        if( m_data->plugins().contains( dpId )) {
            auto dep = m_data->plugins().value( dpId ).get();
            result = initializePlugin( dep, loadedPluginIds );
        }
        else {
            QZ_ERROR( "Qz:Core:Ext" )
                    << "Could not find plugin with ID " << dpId << " which is "
                       "required by plugin " << plugin->pluginId();
            result = false;
            break;
        }
    }
    if( result ) {
        auto &pluginType = plugin->pluginType();
        if( pluginType == AbstractAdapterProvider::PLUGIN_TYPE ) {
            auto adapterPgn = dynamic_cast< AbstractAdapterProvider *>(
                        plugin );
            auto adapter = adapterPgn->adapter();
            if( adapter != nullptr ) {
                registerPluginAdapter( adapter );
            }
        }
        else {
            auto adapter = m_data->adapters().value( plugin->pluginType() );
            if( adapter != nullptr ) {
                result = adapter->handlePlugin( plugin );
            }
            else {
                QZ_ERROR( "Qz:Core:Ext" )
                        << "Could not find adapter for plugin type "
                        << plugin->pluginType() << ", required by plugin "
                        << plugin->pluginId() << ". Ignoring...";
            }
        }
        loadedPluginIds.insert( plugin->pluginId() );
    }
    return result;
}


std::size_t PluginManager::loadPluginAt( const QDir &pluginRoot )
{
    QStringList extensions;
#ifdef Q_OS_LINUX
    extensions << "*.so";
#elif defined Q_OS_WIN
    extensions << "*.dll";
#else
    extensions << "*.dylib" << "*.so";
#endif

#ifdef QT_DEBUG
    QDir pluginDir{ pluginRoot.absoluteFilePath( "debug" )};
#else
    QDir pluginDir{ dirInfo.absoluteFilePath() };
#endif

    std::size_t numLoaded = 0;
    QZ_DEBUG( "Qz:Core:Ext" )
            << "Searching for plugins at " << pluginDir.absolutePath();
    auto fileList = pluginDir.entryInfoList( extensions,
                                             QDir::Files,
                                             QDir::NoSort );
    foreach( const auto &info, fileList ) {
        QZ_DEBUG( "Qz:Core:Ext" ) << info.absoluteFilePath();
        if( info.fileName().startsWith( "plugin_" )
                || info.fileName().startsWith( "libplugin_" )) {
            numLoaded = numLoaded + load( info.absoluteFilePath() );
        }
    }
    return numLoaded;
}

std::size_t PluginManager::load( const QString &pluginFilePath )
{
    std::size_t numLoaded = 0;
    auto lib = std::make_shared< QLibrary >( pluginFilePath );
    lib->load();
    if( lib->isLoaded() ) {
        auto func = reinterpret_cast< PluginFunc >(
                    lib->resolve( PLUGIN_FUNC_NAME ));
        if( func != nullptr ) {
            auto wrapper = func();
            foreach( auto &plugin, wrapper->pluginList ) {
                m_data->plugins().insert( plugin->pluginId(), plugin );
            }
            m_data->libraries().append( lib );
            ++ numLoaded;
        }
        else {
            lib->unload();
            QZ_ERROR( "Qz:Core:Ext" )
                    << "Plugin library at " << pluginFilePath  << " does "
                    << "not export entry point";
        }
    }
    else {
        QZ_ERROR( "Qz:Core:Ext" )
                << "Failed to load plugin library at " << pluginFilePath;
    }
}

}
