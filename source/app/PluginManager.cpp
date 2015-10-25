#include <QSet>

#include <vqcore/logger/VQLogger.h>
#include <vqcore/VQCommon.h>

#include "PluginManager.h"

namespace Vam { namespace Quartz {

bool PluginManager::loadAll()
{
    bool result = true;
    m_libraries = m_loader.loadAll( m_location );
    QSet< QString > loadedBundles;
    for( BundleLibrary::Ptr blib : m_libraries.values() ) {
        const PluginBundle &bundle = blib->bundle();
        if( ! loadedBundles.contains( bundle.bundleId() )) {
            if( ! loadBundle( bundle, loadedBundles )) {
                VQ_ERROR( "Quartz:Core" )
                        << "Could not load bundle with ID "
                        << bundle.bundleId();
            }
        }
    }
    return result;
}


bool PluginManager::unloadAll()
{
    bool result = true;
    m_libraries = m_loader.loadAll( m_location );
    QSet< QString > unloadedBundles;
    for( BundleLibrary::Ptr blib : m_libraries.values() ) {
        const PluginBundle &bundle = blib->bundle();
        if( ! unloadedBundles.contains( bundle.bundleId() )) {
            if( ! unloadBundle( bundle, unloadedBundles )) {
                VQ_ERROR( "Quartz:Core" )
                        << "Could not unload bundle with ID "
                        << bundle.bundleId();
            }
        }
    }
    return result;
}


bool PluginManager::reloadAll()
{
    bool result = unloadAll();
    result = result && loadAll();
    return result;
}


bool PluginManager::unload( QString bundleId )
{
    bool result = false;
    BundleLibrary::Ptr blib = m_libraries.value( bundleId );
    if( blib != nullptr ) {
        QSet< QString > unloadedBundles;
        result = unloadBundle( blib->bundle(), unloadedBundles );
    }
    return result;
}


bool PluginManager::load( QString bundleId )
{
    bool result = false;
    BundleLibrary::Ptr blib = m_libraries.value( bundleId );
    if( blib != nullptr ) {
        QSet< QString > loadedBundles;
        result = loadBundle( blib->bundle(), loadedBundles );
    }
    return result;
}


bool PluginManager::reload( QString bundleId )
{
    bool result = unload( bundleId );
    result = result && load( bundleId );
    return result;
}


bool PluginManager::loadBundle( const PluginBundle &bundle,
                                VQ_IN_OUT QSet< QString > &loadedBundles )
{
    bool result = true;
    const QStringList &bundleDeps = bundle.dependencies();
    for( const QString &dep : bundleDeps ) {
        BundleLibrary::Ptr blib = m_libraries.value( dep );
        if( blib != nullptr ) {
            PluginBundle &depBundle = blib->bundle();
            if( ! loadedBundles.contains( depBundle.bundleId() )) {
                if( ! loadBundle( depBundle, loadedBundles )) {
                    result = false;
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
    if( result ) {
        for( int i = 0; i < bundle.pluginCount(); ++ i ) {
            IQuartzPlugin *plugin = bundle.pluginAt( i );
            if( ! plugin->init( *m_context )) {
                VQ_WARN( "Quartz:Core" )
                        << "Could not initialize plugin with ID "
                        << plugin->pluginId();
                result = false;
            }
            else {
                VQ_DEBUG( "Quartz:Core")
                        << "Initialized plugin " << plugin->pluginId();
            }
        }
    }
    return result;
}


bool PluginManager::unloadBundle( const PluginBundle &bundle,
                                  VQ_IN_OUT QSet< QString > &unloadedBundles )
{
    bool result = true;
    const QList< QString > dependents = m_dependents.values(
                bundle.bundleId() );
    for( const QString &dep : dependents ) {
        if( m_libraries.contains( dep )) {
            BundleLibrary::Ptr blib = m_libraries.value( dep );
            PluginBundle &depBundle = blib->bundle();
            if( ! unloadedBundles.contains( depBundle.bundleId() )) {
                if( unloadBundle( depBundle, unloadedBundles )) {
                    result = false;
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
                result = false;
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
            result = false;
        }
        else {
            VQ_DEBUG( "Quartz:Core" )
                    << "Unloaded library for bundle "
                    << bundle.bundleId();
        }
    }
    return result;
}

} }
