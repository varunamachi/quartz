#include <memory>

#include <QHash>
#include <QDir>
#include <QLibrary>
#include <QSet>
#include <QDebug>

#include "../logger/Logging.h"
#include "../QzCoreContext.h"
#include "Extension.h"
#include "IExtensionAdapter.h"
#include "PluginManager.h"
#include "Plugin.h"
#include "PluginEnv.h"

namespace Quartz { namespace Ext {

struct PluginInfo
{
    PluginInfo()
        : m_plugin{ nullptr }
        , m_library{}
    {

    }

    PluginInfo( Plugin *plugin,
                std::shared_ptr< QLibrary > library )
        : m_plugin{ plugin }
        , m_library{ library }
    {

    }

    bool isValid() const
    {
        return ! ( m_plugin == nullptr || m_library == nullptr );
    }

    Plugin *m_plugin;

    std::shared_ptr< QLibrary > m_library;
};

using ExtensionMap = QHash< QString, std::shared_ptr< Extension >>;
using AdapterMap = QHash< QString, std::shared_ptr< IExtensionAdapter >>;
using PluginInfoMap = QHash< QString, PluginInfo >;

typedef PluginWrapper ( *PluginFunc )( PluginInputWrapper * );
typedef void ( *PluginDestroyerFunc )();

static const char * PLUGIN_GET_FUNC_NAME = "getPluginWrapper";
static const char * PLUGIN_DESTROY_FUNC_NAME = "destroy";


class PluginManager::Impl
{
public:
    bool load( const QDir &dir );

    bool destroy();

    std::size_t loadPlugins( const QDir &pluginRoot,
                             QZ_OUT PluginInfoMap &pluginInfoOut );

    PluginInfo getPlugin( const QString &pluginRoot,
                          const QString &pluginFilePath );
    bool processPlugins( const PluginInfo &pluginInfo,
                         const PluginInfoMap &loadedPlugins,
                         QZ_OUT QSet< QString > &processedPlugins );

    bool initPlugin( Plugin *plugin );

    void registerPluginAdapter( std::shared_ptr< IExtensionAdapter > adapter );

    AdapterMap m_adapters;

    PluginInfoMap m_plugins;

    bool m_active;
};

bool PluginManager::Impl::load( const QDir &dir )
{
    bool result = true;
    auto dirList = dir.entryInfoList( QDir::Dirs | QDir::NoDotAndDotDot,
                                      QDir::SortFlag::NoSort );
    PluginInfoMap loadedPlugins;
    foreach(const QFileInfo &info, dirList) {
        if( info.isReadable() ) {
            QDir pluginDir{ info.absoluteFilePath() };
            auto numLoaded = loadPlugins( pluginDir, loadedPlugins );
            QZ_DEBUG( "Qz:Core:Ext" )
                    << "Loaded " << numLoaded << " extensions from "
                    << info.absoluteFilePath();
        }
        else {
            QZ_WARN( "Qz:Core:Ext" ) << "Could not read plugin directory at "
                                     << info.absoluteFilePath();
            result = false;
        }
    }
    QSet< QString > processed;
    for( auto it = loadedPlugins.begin(); it != loadedPlugins.end(); ++ it ) {
        const auto &pinfo = it.value();
        if( ! processed.contains( pinfo.m_plugin->pluginId() )) {
            result = processPlugins( pinfo,
                                     loadedPlugins,
                                     processed ) && result;
        }
    }
    //unload failed plugins
    for( auto it = loadedPlugins.begin();
         it != loadedPlugins.end();
         ++ it ) {
        auto &pinfo = it.value();
        if( ! m_plugins.contains( pinfo.m_plugin->pluginId() )) {
            auto lib = pinfo.m_library;
            if( lib != nullptr ) {
                auto destroyFunc = reinterpret_cast< PluginDestroyerFunc >(
                            lib->resolve( PLUGIN_DESTROY_FUNC_NAME ));
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
            QZ_DEBUG( "Qz:Core:Ext" )
                    << "Unloaded library for plugin with id " <<
                       pinfo.m_plugin->pluginId()
                    << " which failed to initialize";
        }
        else {
            initPlugin( pinfo.m_plugin );
        }
    }
    return result;
}

std::size_t PluginManager::Impl::loadPlugins(
        const QDir &pluginRoot,
        QZ_OUT PluginInfoMap &pluginInfoOut )
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
        QDir pluginDir = pluginRoot;
#endif
    std::size_t numLoaded = 0;
    QZ_DEBUG( "Qz:Core:Ext" )
            << "Searching for plugins at " << pluginDir.absolutePath();
    auto fileList = pluginDir.entryInfoList( extensions,
                                             QDir::Files,
                                             QDir::NoSort );
    foreach( const auto &info, fileList ) {
        if( info.fileName().startsWith( "plugin_" )
                || info.fileName().startsWith( "libplugin_" )) {

            auto pinfo = getPlugin( pluginRoot.absolutePath(),
                                    info.absoluteFilePath() );
            if( pinfo.isValid() ) {
                pluginInfoOut.insert( pinfo.m_plugin->pluginId(), pinfo );
                ++ numLoaded;
            }
        }
    }
    return numLoaded;
}

PluginInfo PluginManager::Impl::getPlugin( const QString &pluginRoot,
                                           const QString &pluginFilePath )
{
    auto lib = std::make_shared< QLibrary >( pluginFilePath );
    lib->load();
    PluginInfo pinfo{};
    if( lib->isLoaded() ) {
        auto func = reinterpret_cast< PluginFunc >(
                    lib->resolve( PLUGIN_GET_FUNC_NAME ));
        if( func != nullptr ) {
            auto pluginEnv = std::unique_ptr< PluginEnv >{
                new PluginEnv{ pluginRoot, lib->fileName(), "0.1.0000" }};
            PluginInputWrapper input{ std::move( pluginEnv ),
                                      QzCoreContext::get() };
            auto wrapper = func( &input );
            if( wrapper.enabled && wrapper.plugin != nullptr ) {
                pinfo = PluginInfo{ wrapper.plugin, lib };
            }
            else if (wrapper.plugin == nullptr){
                QZ_WARN( "Qz:Core:Ext" )
                        << "Library at " << pluginFilePath << " does not "
                           "contain any plugin, unloading...";
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
    return pinfo;
}

bool PluginManager::Impl::processPlugins(
        const PluginInfo &pluginInfo,
        const PluginInfoMap &loadedPlugins,
        QZ_OUT QSet< QString > &processedPlugins )
{
    if( processedPlugins .contains( pluginInfo.m_plugin->pluginId() )) {
        return true;
    }
    bool result = true;
    const auto &hardDeps = pluginInfo.m_plugin->dependencies();
    for( auto i = 0; i < hardDeps.size(); ++ i ) {
        const auto & plgEntry = hardDeps.at( i );
        auto plgInfo = m_plugins.value( plgEntry.first );
        if( plgInfo.isValid() ) {
            result = processPlugins( plgInfo,
                                     loadedPlugins,
                                     processedPlugins  );
        }
        else {
            result = false;
        }
        if( ! result && plgEntry.second == DependencyType::Optional ) {
            QZ_DEBUG( "Qz:Core:Ext" )
                    << "Optional dependency " << plgEntry.first << " for "
                    << pluginInfo.m_plugin->pluginId() << " not present, "
                       "hence ignored.";
            continue;
        }
        else if( ! result ) {
            QZ_ERROR( "Qz:Core:Ext" )
                    << "Could not initialize plugin with id "
                    << pluginInfo.m_plugin->pluginId()
                    << "; could not find required dependncy with id "
                    << plgEntry.first;
            break;
        }
    }
    if( result ) {
        m_plugins.insert( pluginInfo.m_plugin->pluginId(), pluginInfo );
        QZ_DEBUG( "Qz:Core:Ext" )
                << "Successfuly processed plugin with id "
                << pluginInfo.m_plugin->pluginId();
    }
    processedPlugins .insert( pluginInfo.m_plugin->pluginId() );

    return result;
}

bool PluginManager::Impl::initPlugin( Plugin *plugin)
{
    const auto &adapters = plugin->adapters();
    for( int i = 0; i < adapters.size(); ++ i ) {
        const auto adapter = adapters.at( i );
        if( ! m_adapters.contains( adapter->extensionType() )) {
            m_adapters.insert( adapter->extensionType(), adapter );
        }
    }
    auto result = true;
    const auto extensions = plugin->extensions();
    for( auto i = 0; i < extensions.size(); ++ i ) {
        auto extension = extensions.at( i );
        auto adapter = m_adapters.value( extension->extensionType() );
        if( adapter != nullptr ) {
            result = adapter->handleExtension( extension.get() );
        }
        else {
            QZ_ERROR( "Qz:Core:Ext" )
                    << "Could not find adapter for extension type "
                    << extension->extensionType() << ", required by extension "
                    << extension->extensionId() << ". Ignoring...";
            result = false;
        }
    }
    return result;
}

void PluginManager::Impl::registerPluginAdapter(
        std::shared_ptr< IExtensionAdapter > adapter )
{
    if( adapter ) {
        m_adapters[ adapter->extensionType() ] = adapter;
    }
}

bool PluginManager::Impl::destroy()
{
    if( ! m_active ) {
        return false;
    }
    bool result = true;
    for( auto it = m_adapters.begin();
         it != m_adapters.end();
         ++ it ) {
        auto &handler = it.value();
        result = result && handler->finalizeExtension();
    }
    foreach( auto &plugin, m_plugins ) {
        auto lib = plugin.m_library;
        if( lib != nullptr ) {
            auto destroyFunc = reinterpret_cast< PluginDestroyerFunc >(
                        lib->resolve( PLUGIN_DESTROY_FUNC_NAME ));
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
    m_active = false;
    return result;
}

//========================== PluginManager ====================================
PluginManager::PluginManager()
//    : m_data( std::make_unique< PluginManager::Data >() )
    : m_impl( std::unique_ptr< Impl >( new Impl() ))
{

}


PluginManager::~PluginManager()
{
    destroy();
}

void PluginManager::registerPluginAdapter(
        std::shared_ptr< IExtensionAdapter > adapter )
{
    m_impl->registerPluginAdapter( adapter );
}

void PluginManager::registerPluginAdapter( IExtensionAdapter *adapter )
{
    std::shared_ptr< IExtensionAdapter > adptr{ adapter,
                                                []( IExtensionAdapter *){ }};
    m_impl->registerPluginAdapter(  adptr );
}

const QVector< const Plugin * > PluginManager::plugins() const
{
    QVector< const Plugin *> plugins;
    for( auto it = m_impl->m_plugins.begin();
         it != m_impl->m_plugins.end();
         ++ it )
    {
        plugins.push_back( it->m_plugin );
    }
    return plugins;
}

const Plugin * PluginManager::plugin( const QString &pluginId ) const
{
    Plugin *plugin = nullptr;
    if( m_impl->m_plugins.contains( pluginId )) {
        const auto &pinfo = m_impl->m_plugins.value( pluginId );
        plugin = pinfo.m_plugin;
    }
    return plugin ;
}

const QLibrary * PluginManager::libraryForPlugin(
        const QString &pluginId ) const
{
    QLibrary *library = nullptr;
    if( m_impl->m_plugins.contains( pluginId )) {
        const auto &pinfo = m_impl->m_plugins.value( pluginId );
        library = pinfo.m_library.get();
    }
    return library ;
}

bool PluginManager::loadFrom( const QString &location )
{
    bool result = false;
    QFileInfo info{ location };
    if( info.isDir() && info.isReadable() ) {
        result = m_impl->load( QDir{ location });
    }
    else {
        QZ_ERROR( "Qz:Core:Ext" )
                << "Invalid plugin root directory " << location << " given";
    }
    return result;
}

bool PluginManager::destroy()
{
    return m_impl->destroy();
}

} }
