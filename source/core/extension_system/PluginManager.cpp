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
    BundleInfo()
        : m_bundle{ nullptr }
        , m_library{}
    {

    }

    BundleInfo( AbstractPluginBundle *bundle,
                std::shared_ptr< QLibrary > library )
        : m_bundle{ bundle }
        , m_library{ library }
    {

    }

    bool isValid() const
    {
        return m_bundle == nullptr || m_library == nullptr;
    }

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


class PluginManager::Impl
{
public:
    std::size_t loadPluginAt( const QDir &pluginRoot );

    std::size_t load( const QString &pluginRoot,
                      const QString &pluginFilePath );

    bool initializePlugin( AbstractPlugin *plugin,
                           QZ_IN_OUT QSet< QString > &loadedPluginIds );

    void registerAdapter( IPluginAdapter *pluginAdapter );

    bool processBundles();

    bool processBundles( const BundleInfo &bundleInfo,
                         DependencyType depType,
                         QZ_OUT QSet< QString > &processedBundles );

    bool initBundle( AbstractPluginBundle *bundle );

    PluginMap m_plugins;

    AdapterMap m_adapters;

    BundleInfoMap m_bundles;

    bool m_active;
};


PluginManager::PluginManager()
//    : m_data( std::make_unique< PluginManager::Data >() )
    : m_impl( std::unique_ptr< Impl >( new Impl() ))
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
            auto numLoaded = m_impl->loadPluginAt( pluginDir );
            QZ_DEBUG( "Qz:Core:Ext" )
                    << "Loaded " << numLoaded << " plugins from "
                    << info.absoluteFilePath();
        }
        else {
            QZ_WARN( "Qz:Core:Ext" ) << "Could not read plugin directory at "
                                     << info.absoluteFilePath();
        }
    }
    QZ_INFO( "Qz:Core:Ext" ) << "Initilizing " << m_impl->m_plugins.size()
                             << "plugins from " << location;
    if( ! m_impl->m_plugins.isEmpty() ) {
        QSet< QString > loaded;
        for( auto pit = m_impl->m_plugins.begin();
             pit != m_impl->m_plugins.end();
             ++ pit ) {
            auto &plugin = pit.value();
            if( ! loaded.contains( plugin->pluginId() )) {
                m_impl->initializePlugin( plugin.get(), loaded );
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
    if( ! m_impl->m_active ) {
        return false;
    }
    bool result = true;
    for( auto it = m_impl->m_adapters.begin();
         it != m_impl->m_adapters.end();
         ++ it ) {
        auto &handler = it.value();
        result = result && handler->finalizePlugins();
    }
    foreach( auto &bundle, m_impl->m_bundles ) {
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
    m_impl->m_active = false;
    return result;
}


AbstractPlugin * PluginManager::plugin( const QString &id ) const
{
    auto &plugin = m_impl->m_plugins.value( id );
    return plugin.get();
}


IPluginAdapter * PluginManager::adapter( const QString &id ) const
{
    return m_impl->m_adapters.value( id );
}


void PluginManager::registerPluginAdapter( IPluginAdapter *pluginAdapter )
{
    m_impl->registerAdapter( pluginAdapter );
}

void PluginManager::Impl::registerAdapter( IPluginAdapter *pluginAdapter )
{
    if( ! m_adapters.contains( pluginAdapter->pluginType() )) {
        m_adapters.insert( pluginAdapter->pluginType(), pluginAdapter );
    }
}

bool PluginManager::Impl::processBundles()
{
    return false;
}

bool PluginManager::Impl::processBundles(
        const BundleInfo &bundleInfo,
        DependencyType depType,
        QZ_OUT QSet< QString > &processedBundles )
{
    if( ! initBundle( bundleInfo.m_bundle )) {
        ///TODO log error
        return false;
    }
    bool result = true;
    const auto &hardDeps = bundleInfo.m_bundle->dependencies( depType );
    for( int i = 0; i < hardDeps.size(); ++ i ) {
        const auto & depId = hardDeps.at( i );
        auto depInfo = m_bundles.value( depId );
        if( depInfo.isValid() ) {
            result = processBundles( depInfo, depType, processedBundles )
                     && initBundle( depInfo.m_bundle );
        }
        else {
            result = false;
        }

        if( ! result && depType == DependencyType::Optional ) {
            ///TODO log debug
            continue;
        }
        else if( ! result ) {
            ///TODO log error
            break;
        }

    }
    return result;
}

bool PluginManager::Impl::initBundle( AbstractPluginBundle *bundle )
{
    return true;
}


bool PluginManager::Impl::initializePlugin( AbstractPlugin *plugin,
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
                    registerAdapter( adapter );
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
            auto adapter = m_adapters.value( plugin->pluginType() );
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


std::size_t PluginManager::Impl::loadPluginAt( const QDir &pluginRoot )
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

std::size_t PluginManager::Impl::load(
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
                    m_plugins.insert( plugin->pluginId(), plugin );
                }
                m_bundles.insert( bundle->bundleId(), info );
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
