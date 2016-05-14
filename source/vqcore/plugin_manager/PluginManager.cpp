#include <QSet>

#include <vqcore/VQCommon.h>
#include <vqcore/logger/Logging.h>

#include "PluginManager.h"

namespace Vam {

Result< bool > PluginManager::loadAll()
{
    Result< bool > result;
    m_libraries = m_loader.loadAll( m_location );
    QSet< QString > loadedBundles;
    for( auto &blib : m_libraries.values() ) {
        auto &bundle = blib->bundle();
        if( ! loadedBundles.contains( bundle.bundleId() )) {
            result = loadBundle( bundle, loadedBundles );
            if( ! result ) {
                VQ_ERROR( "Quartz:Core" )
                        << "Could not load bundle with ID "
                        << bundle.bundleId();
            }
        }
    }
    return result;
}


Result< bool > PluginManager::unloadAll()
{
    Result< bool > result;
    m_libraries = m_loader.loadAll( m_location );
    QSet< QString > unloadedBundles;
    for( auto & blib : m_libraries.values() ) {
        auto &bundle = blib->bundle();
        if( ! unloadedBundles.contains( bundle.bundleId() )) {
            result = unloadBundle( bundle, unloadedBundles );
            if( ! result ) {
                VQ_ERROR( "Quartz:Core" )
                        << "Could not unload bundle with ID "
                        << bundle.bundleId();
            }

        }
    }
    return result;
}


Result< bool > PluginManager::reloadAll()
{
    auto result = unloadAll();
     if( result.result() ) {
         result = loadAll();
     }
    return result;
}


Result< bool > PluginManager::unload( QString bundleId )
{
    Result< bool > result;
    BundleLibrary::Ptr blib = m_libraries.value( bundleId );
    if( blib != nullptr ) {
        QSet< QString > unloadedBundles;
        result = unloadBundle( blib->bundle(), unloadedBundles );
    }
    else {
        result = Result< bool >::failure(
                    QObject::tr( "Could not find library for bundleID " )
                                 + bundleId );
    }
    return result;
}


Result< bool > PluginManager::load( QString bundleId )
{
    Result< bool > result;
    auto &blib = m_libraries.value( bundleId );
    if( blib != nullptr ) {
        QSet< QString > loadedBundles;
        result = loadBundle( blib->bundle(), loadedBundles );
    }
    else {
        result = Result< bool >::failure(
                    QObject::tr( "Could not find library for bundleID " )
                    + bundleId );
    }
    return result;
}


Result< bool > PluginManager::reload( QString bundleId )
{
    Result< bool > result = unload( bundleId );
    if( result.result() ) {
        result = load( bundleId );
    }
    return result;
}

Result< PluginBundle * > PluginManager::pluginBundle(
        const QString &bundleId) const
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


Result< QList< const PluginBundle * >> PluginManager::allBundles() const
{
    QList< const PluginBundle * > bundles;
    auto it = m_libraries.begin();
    for( ; it != m_libraries.end(); ++ it ) {
        auto &bundle = ( *it )->bundle();
        bundles.append( &bundle );
    }
    return Result< QList< const PluginBundle *>>::success( bundles );
}


Result< bool > PluginManager::loadBundle(
        const PluginBundle &bundle,
        VQ_IN_OUT QSet< QString > &loadedBundles )
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


Result< bool > PluginManager::unloadBundle(
        const PluginBundle &bundle,
        VQ_IN_OUT QSet< QString > &unloadedBundles )
{
    Result< bool > result = Result< bool >::success();
    const QList< QString > dependents = m_dependents.values(
                bundle.bundleId() );
    for( const QString &dep : dependents ) {
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
