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

    Result< std::size_t > allBundles(
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
    for( auto &bpair : m_libraries ) {
        const auto &bundle = bpair.second->bundle();
        if( loadedBundles.find( bundle->bundleId() )
                == std::end( loadedBundles )) {
            result = loadBundle( *bundle, loadedBundles );
        }
        if( ! result ) {
            VQ_ERROR( "Quartz:Core" )
                    << "Could not load bundle with ID "
                    << bundle->bundleId();
        }
    }
    return result;
}


Result< bool > PluginManager::Impl::unloadAll()
{
    Result< bool > result;
//    m_libraries = m_loader.loadAll( m_location );
    std::unordered_set< std::string > unloadedBundles;
    for( auto & blib : m_libraries ) {
        const auto &bundle = blib.second->bundle();
        if( ! STLUtils::contains( unloadedBundles, bundle->bundleId() )) {
            result = unloadBundle( *bundle, unloadedBundles );
            if( ! result ) {
                VQ_ERROR( "Quartz:Core" )
                        << "Could not unload bundle with ID "
                        << bundle->bundleId();
            }

        }
    }
    return result;
}


Result< bool > PluginManager::Impl::reloadAll()
{
    auto result = unloadAll();
     if( result.result() ) {
         result = loadAll();
     }
    return result;
}


Result< bool > PluginManager::Impl::unload( const std::string &bundleId )
{
    Result< bool > result;
    auto it = m_libraries.find( bundleId );
    if( it != std::end( m_libraries )) {
        std::unordered_set< std::string > unloadedBundles;
        result = unloadBundle( *it->second->bundle(), unloadedBundles );
    }
    else {
        result = Result< bool >::failure(
                    "Could not find library for bundleID " + bundleId );
    }
    return result;
}


Result< bool > PluginManager::Impl::load( const std::string &bundleId )
{
    Result< bool > result;
    auto it = m_libraries.find( bundleId );
    if( it != std::end( m_libraries )) {
        std::unordered_set< std::string > loadedBundles;
        result = loadBundle( *it->second->bundle(), loadedBundles );
    }
    else {
        result = Result< bool >::failure(
                    "Could not find library for bundleID " + bundleId );
    }
    return result;
}


Result< bool > PluginManager::Impl::reload( const std::string &bundleId )
{
    Result< bool > result = unload( bundleId );
    if( result.result() ) {
        result = load( bundleId );
    }
    return result;
}


Result< PluginBundle * > PluginManager::Impl::pluginBundle(
        const std::string &bundleId) const
{
    auto result = Result< PluginBundle * >::failure(
                nullptr,
                "Could not find bundle with id " + bundleId );
    auto it = m_libraries.find( bundleId );
    if( it != std::end( m_libraries )) {
        auto bundle = it->second->bundle();
        result = Result< PluginBundle *>::success( bundle );
    }
    return result;
}


Result< std::size_t > PluginManager::Impl::allBundles(
        VQ_OUT std::vector< const PluginBundle * > &bundlesOut ) const
{
    auto numBundles = std::size_t( 0 );
    for( const auto &blibp : m_libraries ) {
        const auto &bundle = blibp.second->bundle();
        bundlesOut.emplace_back( bundle );
        ++ numBundles;
    }
    return Result< std::size_t >::success( numBundles );
}


Result< bool > PluginManager::Impl::loadBundle(
        const PluginBundle &bundle,
        VQ_IN_OUT std::unordered_set< std::string > &loadedBundles )
{
    auto result = Result< bool >::success();
    const auto &bundleDeps = bundle.dependencies();
    for( const auto &dep : bundleDeps ) {
        auto it = m_libraries.find( dep );
        if( it != std::end( m_libraries )) {
            const auto &depBundle = it->second->bundle();
            if( STLUtils::contains( loadedBundles, depBundle->bundleId() )){
                result = loadBundle( *depBundle, loadedBundles );
                if( ! result ) {
                    VQ_ERROR( "Vq:Ext" )
                            << "Could not load dependency bundle "
                            << depBundle->bundleId();
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
        for( std::size_t i = 0; i < bundle.pluginCount(); ++ i ) {
            auto plugin = bundle.pluginAt( i );
            if( ! plugin->init() ) {
                VQ_WARN( "Vq:Ext" )
                        << "Could not initialize plugin with ID "
                        << plugin->pluginId();
                result = Result< bool >::failure(
                            "Could not initialize plugin" );
            }
            else {
                VQ_DEBUG( "Vq:Ext" )
                        << "Initialized plugin " << plugin->pluginId();
            }
        }
    }
    return result;
}


Result< bool > PluginManager::Impl::unloadBundle(
        const PluginBundle &bundle,
        VQ_IN_OUT std::unordered_set< std::string > &unloadedBundles )
{
    Result< bool > result = Result< bool >::success();
    auto rangeIt = m_dependents.equal_range( bundle.bundleId() );
    for( auto it = rangeIt.first; it != rangeIt.second; ++ it ) {
        auto dep = it->second;
        auto libIt = m_libraries.find( dep );
        if( libIt != std::end( m_libraries )) {
            auto depBundle = libIt->second->bundle();
            if( ! STLUtils::contains( unloadedBundles, depBundle->bundleId() )){
                result = unloadBundle( *depBundle, unloadedBundles );
                if( ! result ) {
                    result = Result< bool >::failure(
                                "Could not unload dependent bundle" );
//                    VQ_ERROR( "Quartz:Core" )
//                            << "Could not unload bundle "
//                            << depBundle.bundleId() << " on which bundle "
//                            << bundle.bundleId() << " depends.";
                    break;
                }
            }
        }
        else {
            //TODO Warn
        }
    }

    if( result ) {
        //remove the dependents
        m_dependents.erase( rangeIt.first, rangeIt.second );
        for( std::size_t i = 0; i < bundle.pluginCount(); ++ i ) {
            auto plugin = bundle.pluginAt( i );
            result = plugin->uninit();
            if( ! result ) {
//                VQ_WARN( "Quartz:Core" )
//                        << "Could not finalize plugin with ID "
//                        << plugin->pluginId();
                result = Result< bool >::failure( "Failed to finalize plugin" );
            }
            else {
//                VQ_DEBUG( "Quartz:Core")
//                        << "Initialized plugin " << plugin->pluginId();
            }
        }
    }
    if( result && STLUtils::contains( m_libraries, bundle.bundleId() )) {
        auto libIt = m_libraries.find( bundle.bundleId() );
        if( libIt != std::end( m_libraries )) {
            auto &lib = libIt->second;
            result = lib->library()->unload();
            if( ! result  ) {
//                VQ_ERROR( "Quartz:Core" )
//                        << "Could not unload library for bundle "
//                        << bundle.bundleId() << ": "
//                        << result.reason();
            }
            else {
//                VQ_DEBUG( "Quartz:Core" )
//                        << "Unloaded library for bundle "
//                        << bundle.bundleId();
            }
        }
    }
    return result;
}

}
