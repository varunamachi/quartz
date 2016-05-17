#include <unordered_set>
#include <unordered_map>

#include "../common/Macros.h"
#include "../common/ContainerOperations.h"
#include "../logger/Logging.h"
#include "BundleLibrary.h"
#include "BundleLoader.h"
#include "PluginManager.h"
#include "PluginBundle.h"

namespace Vam {

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

    Result< bool > allBundles(
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
    m_libraries = m_loader.loadAll( m_location );
    std::unordered_set< std::string > loadedBundles;
    for( auto &bpair : m_libraries ) {
        const auto &bundle = bpair.second->bundle();
        if( loadedBundles.find( bundle->bundleId() )
                == std::end( loadedBundles )) {
            result = loadBundle( *bundle, loadedBundles );
        }
        if( ! result ) {
//            VQ_ERROR( "Quartz:Core" )
//                    << "Could not load bundle with ID "
//                    << bundle.bundleId();
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
        if( ! ContainerOps::contains( unloadedBundles, bundle->bundleId() )) {
            result = unloadBundle( *bundle, unloadedBundles );
            if( ! result ) {
//                VQ_ERROR( "Quartz:Core" )
//                        << "Could not unload bundle with ID "
//                        << bundle.bundleId();
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


Result< bool > PluginManager::Impl::unload( std::string bundleId )
{
    Result< bool > result;
    BundleLibPtr lib = m_libraries.value( bundleId );
    if( blib != nullptr ) {
        QSet< std::string > unloadedBundles;
        result = unloadBundle( blib->bundle(), unloadedBundles );
    }
    else {
        result = Result< bool >::failure(
                    QObject::tr( "Could not find library for bundleID " )
                                 + bundleId );
    }
    return result;
}


Result< bool > PluginManager::Impl::load( std::string bundleId )
{
    Result< bool > result;
    auto &blib = m_libraries.value( bundleId );
    if( blib != nullptr ) {
        QSet< std::string > loadedBundles;
        result = loadBundle( blib->bundle(), loadedBundles );
    }
    else {
        result = Result< bool >::failure(
                    QObject::tr( "Could not find library for bundleID " )
                    + bundleId );
    }
    return result;
}


Result< bool > PluginManager::Impl::reload( std::string bundleId )
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
                QObject::tr( "Could not find bundle with id " ) + bundleId );
    auto bundleLib = m_libraries.value( bundleId );
    if( bundleLib != nullptr ) {
        auto &bundle = bundleLib->bundle();
        result = Result< PluginBundle *>::success( &bundle );
    }
    return result;
}


Result< QList< const PluginBundle * >> PluginManager::Impl::allBundles() const
{
    QList< const PluginBundle * > bundles;
    auto it = m_libraries.begin();
    for( ; it != m_libraries.end(); ++ it ) {
        auto &bundle = ( *it )->bundle();
        bundles.append( &bundle );
    }
    return Result< QList< const PluginBundle *>>::success( bundles );
}


Result< bool > PluginManager::Impl::loadBundle(
        const PluginBundle &bundle,
        VQ_IN_OUT QSet< std::string > &loadedBundles )
{
    Result< bool > result;
    const auto &bundleDeps = bundle.dependencies();
    for( const auto &dep : bundleDeps ) {
        auto &blib = m_libraries.value( dep );
        if( blib != nullptr ) {
            PluginBundle &depBundle = blib->bundle();
            if( ! loadedBundles.contains( depBundle.bundleId() )) {
                result = loadBundle( depBundle, loadedBundles );
                if( ! result ) {
                    VQ_ERROR( "Quartz:Core" )
                            << "Could not load dependency bundle "
                            << depBundle.bundleId();
                    break;
                }
                else {
                    //make dependents
                    m_dependents.insert( depBundle.bundleId(),
                                         bundle.bundleId() );
                }
            }
        }
    }
    if( result.result() ) {
        for( int i = 0; i < bundle.pluginCount(); ++ i ) {
            auto *plugin = bundle.pluginAt( i );
            if( ! plugin->init( *m_context )) {
                VQ_WARN( "Quartz:Core" )
                        << "Could not initialize plugin with ID "
                        << plugin->pluginId();
                result = Result< bool >::failure(
                            QObject::tr( "Could not initialize plugin" ));
            }
            else {
                VQ_DEBUG( "Quartz:Core")
                        << "Initialized plugin " << plugin->pluginId();
            }
        }
    }
    return result;
}


Result< bool > PluginManager::Impl::unloadBundle(
        const PluginBundle &bundle,
        VQ_IN_OUT QSet< std::string > &unloadedBundles )
{
    Result< bool > result = Result< bool >::success();
    const QList< std::string > dependents = m_dependents.values(
                bundle.bundleId() );
    for( const std::string &dep : dependents ) {
        if( m_libraries.contains( dep )) {
            BundleLibrary::Ptr blib = m_libraries.value( dep );
            PluginBundle &depBundle = blib->bundle();
            if( ! unloadedBundles.contains( depBundle.bundleId() )) {
                if( unloadBundle( depBundle, unloadedBundles )) {
                    result = Result< bool >::failure(
                                "Could not unload dependent bundle" );
                    VQ_ERROR( "Quartz:Core" )
                            << "Could not unload bundle "
                            << depBundle.bundleId() << " on which bundle "
                            << bundle.bundleId() << " depends.";
                    break;
                }
                else {
                    //remove dependents
                    m_dependents.remove( depBundle.bundleId(),
                                         bundle.bundleId() );
                }
            }
        }
    }
    if( result ) {
        for( int i = 0; i < bundle.pluginCount(); ++ i ) {
            IQuartzPlugin *plugin = bundle.pluginAt( i );
            if( ! plugin->uninit( *m_context )) {
                VQ_WARN( "Quartz:Core" )
                        << "Could not finalize plugin with ID "
                        << plugin->pluginId();
                result = Result< bool >::failure( "Failed to finalize plugin" );
            }
            else {
                VQ_DEBUG( "Quartz:Core")
                        << "Initialized plugin " << plugin->pluginId();
            }
        }
    }
    if( result && m_libraries.contains( bundle.bundleId() )) {
        BundleLibrary::Ptr lib = m_libraries.value( bundle.bundleId() );
        if( ! lib->library().unload() ) {
            VQ_ERROR( "Quartz:Core" )
                    << "Could not unload library for bundle "
                    << bundle.bundleId();
            result = Result< bool >::failure( "Library unload failed" );
        }
        else {
            VQ_DEBUG( "Quartz:Core" )
                    << "Unloaded library for bundle "
                    << bundle.bundleId();
        }
    }
    return result;
}

}
