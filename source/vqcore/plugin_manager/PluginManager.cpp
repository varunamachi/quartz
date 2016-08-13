#include <unordered_set>
#include <unordered_map>

#include "../platform/shared_library/SharedLibrary.h"
#include "../common/Macros.h"
#include "../common/STLUtils.h"
#include "../logger/Logging.h"
#include "BundleLibrary.h"
#include "BundleLoader.h"
#include "PluginManager.h"
#include "PluginBundle.h"
#include "AbstractPlugin.h"

namespace Vq {

class PluginManager::Impl
{
    Impl( std::string location )
        : m_location( location )
    {

    }

    Result< bool > loadAll();

    Result< bool > unloadAll();

    Result< bool > reloadAll();

    Result< bool > unload( const std::string &bundleId );

    Result< bool > load( const std::string &bundleId );

    Result< bool > reload( const std::string &bundleId );

    Result< PluginBundle * > pluginBundle( const std::string &bundleId ) const;

    std::size_t allBundles(
            VQ_OUT std::vector< const PluginBundle * > &bundlesOut ) const;

private:
    using BundleLibPtr = std::unique_ptr< BundleLibrary >;

    Result< bool > loadBundle(
            const PluginBundle &bundle,
            VQ_IN_OUT std::unordered_set< std::string > &loadedBundles );

    Result< bool > unloadBundle(
            const PluginBundle &bundle,
            VQ_IN_OUT std::unordered_set< std::string > &unloadedBundles );

    std::unordered_map< std::string, BundleLibPtr > m_libraries;

    std::unordered_multimap< std::string, std::string > m_dependents;

    std::string m_location;

    BundleLoader m_loader;
};




Result< bool > PluginManager::Impl::loadAll()
{
    Result< bool > result;
    m_libraries = m_loader.loadAll( m_location ).data();
    std::unordered_set< std::string > loadedBundles;
    std::size_t processed = 0;
    for( auto &bpair : m_libraries ) {
        const auto &bundle = bpair.second->bundle();
        if( loadedBundles.find( bundle->bundleId() )
                == std::end( loadedBundles )) {
            result = loadBundle( *bundle, loadedBundles );
        }
        if( ! result ) {
            VQ_ERROR( "Vq:Ext" )
                    << "Could not load bundle with ID "
                    << bundle->bundleId() << " - " << result;
        }
        ++ processed;
    }
    if( processed != loadedBundles.size() - 1 ) {
        auto result = R::stream( false )
                << "Failed to load all bundles, loaded " << loadedBundles.size()
                << " out of " << processed << " bundles " << R::fail;
        VQ_ERROR( "Vq:Ext" ) << result;
        return result;
    }
    return R::success( true );
}


Result< bool > PluginManager::Impl::unloadAll()
{
    std::unordered_set< std::string > unloadedBundles;
    std::size_t processed = 0;
    for( auto & blib : m_libraries ) {
        const auto &bundle = blib.second->bundle();
        if( ! STLUtils::contains( unloadedBundles, bundle->bundleId() )) {
            auto result = unloadBundle( *bundle, unloadedBundles );
            if( ! result ) {
                VQ_ERROR( "Vq:Ext" )
                        << "Could not unload bundle with ID "
                        << bundle->bundleId() << result;
            }
            ++ processed;
        }
    }
    if( processed != unloadedBundles.size() - 1 ) {
        auto result = R::stream( false )
                << "Failed to unload all bundles, loaded "
                << unloadedBundles.size() << " out of " << processed
                << " bundles " << R::fail;
        VQ_ERROR( "Vq:Ext" ) << result;
        return result;
    }
    return R::success( true );
}


Result< bool > PluginManager::Impl::reloadAll()
{
    auto result = unloadAll();
     if( result.value() ) {
         result = loadAll();
     }
    return result;
}


Result< bool > PluginManager::Impl::unload( const std::string &bundleId )
{
    auto it = m_libraries.find( bundleId );
    if( it == std::end( m_libraries )) {
        auto result = R::stream( false )
                    << "Could not find library for bundleID " << bundleId
                    << R::fail;
        VQ_ERROR( "Vq:Ext" ) << result;
    }
    std::unordered_set< std::string > unloadedBundles;
    auto result = unloadBundle( *it->second->bundle(), unloadedBundles );
    return result;
}


Result< bool > PluginManager::Impl::load( const std::string &bundleId )
{
    auto it = m_libraries.find( bundleId );
    if( it == std::end( m_libraries )) {
        auto result = R::stream( false )
                << "Could not find library for bundleID " << bundleId
                << R::fail;
        VQ_ERROR( "Vq:Ext" ) << result;

    }
    std::unordered_set< std::string > loadedBundles;
    auto result = loadBundle( *it->second->bundle(), loadedBundles );
    return result;
}


Result< bool > PluginManager::Impl::reload( const std::string &bundleId )
{
    Result< bool > result = unload( bundleId );
    if( result.value() ) {
        result = load( bundleId );
    }
    return result;
}


Result< PluginBundle * > PluginManager::Impl::pluginBundle(
        const std::string &bundleId) const
{
    auto it = m_libraries.find( bundleId );
    if( it == std::end( m_libraries )) {
        auto result = R::stream< PluginBundle *>( nullptr )
                    << "Could not find bundle with id " << bundleId
                    << R::fail;
        VQ_ERROR( "Vq:Ext" ) << result;
        return result;
    }
    auto bundle = it->second->bundle();
    auto result = R::success( std::move( bundle ));
    return result;
}


std::size_t PluginManager::Impl::allBundles(
        VQ_OUT std::vector< const PluginBundle * > &bundlesOut ) const
{
    auto numBundles = std::size_t( 0 );
    for( const auto &blibp : m_libraries ) {
        const auto &bundle = blibp.second->bundle();
        bundlesOut.emplace_back( bundle );
        ++ numBundles;
    }
    return numBundles;
}


Result< bool > PluginManager::Impl::loadBundle(
        const PluginBundle &bundle,
        VQ_IN_OUT std::unordered_set< std::string > &loadedBundles )
{
    auto result = R::success( true );
    const auto &bundleDeps = bundle.dependencies();
    for( const auto &dep : bundleDeps ) {
        auto it = m_libraries.find( dep );
        if( it != std::end( m_libraries )) {
            const auto &depBundle = it->second->bundle();
            if( STLUtils::contains( loadedBundles, depBundle->bundleId() )){
                result = loadBundle( *depBundle, loadedBundles );
                if( ! result ) {
                    result = R::stream( false, result.errorCode() )
                            << "Could not load dependency bundle "
                            << depBundle->bundleId() << " --> "
                            << result.reason() << R::fail;
                    VQ_ERROR( "Vq:Ext" ) << result;
                    break;
                }
                else {
                    m_dependents.insert( std::make_pair( depBundle->bundleId(),
                                                         bundle.bundleId() ));
                }
            }
        }
    }
    if( result ) {
        auto stream = std::move( R::stream( false ));
        int failedPlugins = 0;
        stream << "Failed to initialize plugin(s): ";
        for( std::size_t i = 0; i < bundle.pluginCount(); ++ i ) {
            auto plugin = bundle.pluginAt( i );
            if( ! plugin->init() ) {
                ++ failedPlugins;
                VQ_WARN( "Vq:Ext" ) << "Failed to initialize plugin with ID "
                                    << plugin->pluginId();
                stream << plugin->pluginId();
                if( failedPlugins > 1 ) {
                    stream << ", ";
                }
            }
            else {
                VQ_DEBUG( "Vq:Ext" )
                        << "Initialized plugin " << plugin->pluginId();
            }
        }
        if( failedPlugins != 0 ) {
            result = stream << R::fail;
        }
    }
    return result;
}


Result< bool > PluginManager::Impl::unloadBundle(
        const PluginBundle &bundle,
        VQ_IN_OUT std::unordered_set< std::string > &unloadedBundles )
{
    Result< bool > result = R::success( true );
    auto rangeIt = m_dependents.equal_range( bundle.bundleId() );
    for( auto it = rangeIt.first; it != rangeIt.second; ++ it ) {
        auto dep = it->second;
        auto libIt = m_libraries.find( dep );
        if( libIt != std::end( m_libraries )) {
            auto depBundle = libIt->second->bundle();
            if( ! STLUtils::contains( unloadedBundles, depBundle->bundleId() )){
                result = unloadBundle( *depBundle, unloadedBundles );
                if( ! result ) {
                    result = R::stream( false )
                            << "Could not unload bundle "
                            << depBundle->bundleId() << " on which bundle "
                            << bundle.bundleId() << " depends." << R::fail;
                    VQ_ERROR( "Vq:Ext" ) << result;
                    break;
                }
            }
        }
        else {
            VQ_WARN( "Vq:Ext" ) << "Library entry for bundle "
                                << bundle.bundleId() << " is not found";
        }
    }
    if( result ) {
        //remove the dependents
        m_dependents.erase( rangeIt.first, rangeIt.second );
        for( std::size_t i = 0; i < bundle.pluginCount(); ++ i ) {
            auto plugin = bundle.pluginAt( i );
            result = plugin->uninit();
            if( ! result ) {
                VQ_WARN( "Vq:Ext" )
                        << "Could not finalize plugin with ID "
                        << plugin->pluginId();
            }
            else {
                VQ_DEBUG( "Vq:Ext")
                        << "Initialized plugin " << plugin->pluginId();
            }
        }
    }
    if( result && STLUtils::contains( m_libraries, bundle.bundleId() )) {
        auto libIt = m_libraries.find( bundle.bundleId() );
        if( libIt != std::end( m_libraries )) {
            auto &lib = libIt->second;
            result = lib->library()->unload();
            if( ! result  ) {
                VQ_ERROR( "Vq:Ext" )
                        << "Could not unload library for bundle "
                        << bundle.bundleId() << ": "
                        << result.reason();
            }
            else {
                VQ_DEBUG( "Vq:Ext" )
                        << "Unloaded library for bundle "
                        << bundle.bundleId();
            }
        }
    }
    return result;
}

}
