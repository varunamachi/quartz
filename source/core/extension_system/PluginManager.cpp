#include <memory>

#include <QHash>
#include <QDir>
#include <QLibrary>
#include <QSet>
#include <QDebug>

#include "../logger/Logging.h"
#include "../QzCoreContext.h"
#include "AbstractPlugin.h"
#include "IPluginAdapter.h"
#include "PluginManager.h"
#include "AbstractAdapterProvider.h"
#include "AbstractPluginBundle.h"
#include "BundleEnv.h"

namespace Quartz {

struct BundleInfo
{
    AbstractPluginBundle *m_bundle;

    std::shared_ptr< QLibrary > m_library;
};

using PluginMap = QHash< QString, std::shared_ptr< AbstractPlugin >>;
using AdapterMap = QHash< QString, IPluginAdapter *>;
using BundleInfoMap = QHash< QString, BundleInfo >;

typedef PluginBundleWrapper ( *PluginFunc )( BundleInputWrapper * );
typedef void ( *BundleDestroyerFunc )();

static const char * PLUGIN_GET_FUNC_NAME = "getBundleWrapper";
static const char * BUNDLE_DESTROY_FUNC_NAME = "destroy";


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

    BundleInfoMap & bundles()
    {
        return m_bundles;
    }

    const BundleInfoMap & bundles() const
    {
        return m_bundles;
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

    BundleInfoMap m_bundles;

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
    foreach( auto &bundle, m_data->bundles() ) {
        auto lib = bundle.m_library;
        if( lib != nullptr ) {
            auto destroyFunc = reinterpret_cast< BundleDestroyerFunc >(
                        lib->resolve( BUNDLE_DESTROY_FUNC_NAME ));
            if( destroyFunc != nullptr ) {
                destroyFunc();
            }
            else {
                QZ_DEBUG( "Qz:Core:Ext" )
                        << "Could not find symbol for destroy function in "
                           " library: " << lib->fileName();
            }
            result = result && lib->unload();
        }
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
    if( result ) {
        auto &pluginType = plugin->pluginType();
        if( pluginType == AbstractAdapterProvider::PLUGIN_TYPE ) {
            auto adapterPgn = dynamic_cast< AbstractAdapterProvider *>(
                        plugin );
            if( adapterPgn != nullptr ) {
                auto adapters = adapterPgn->adapters();
                foreach( auto adapter, adapters ) {
                    registerPluginAdapter( adapter );
                }
            }
            else {
                QZ_ERROR( "Qz:Core:Ext" )
                        << "Invalid adapter plugin provided "
                        << ( plugin != nullptr ? plugin->pluginId()
                                               : "<null>" );
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
//    QDir pluginDir{ dirInfo.absoluteFilePath() };
        QDir pluginDir = pluginRoot;
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
            numLoaded = numLoaded + load( pluginRoot.absolutePath(),
                                          info.absoluteFilePath() );
        }
    }
    return numLoaded;
}

std::size_t PluginManager::load(
        const QString &pluginRoot,
        const QString &pluginFilePath )
{
    std::size_t numLoaded = 0;
    auto lib = std::make_shared< QLibrary >( pluginFilePath );
    lib->load();
    if( lib->isLoaded() ) {
        auto func = reinterpret_cast< PluginFunc >(
                    lib->resolve( PLUGIN_GET_FUNC_NAME ));
        if( func != nullptr ) {
            auto bundleEnv = std::unique_ptr< BundleEnv >{
                new BundleEnv{ pluginRoot, lib->fileName(), "0.1.0000" }};
            BundleInputWrapper input{ std::move( bundleEnv ),
                        QzCoreContext::get() };
            auto bundle = func( &input ).bundle;
            if( bundle != nullptr ) {
                auto info = BundleInfo{ bundle, lib };
                foreach( auto plugin, bundle->plugins() ) {
                    m_data->plugins().insert( plugin->pluginId(), plugin );
                }
                m_data->bundles().insert( bundle->bundleId(), info );
                ++ numLoaded;
            }
            else {
                //print warning...
                lib->unload();
            }
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
    return numLoaded;
}

}
