
#include <QDir>
#include <QApplication>

#include "../logger/Logging.h"
#include "PluginBundleInterface.h"

#include "BundleLoader.h"

namespace Vam {


const char * INTERFACE_FUNC_NAME = "pluginBundle";
typedef BundleWrapper ( *PluginFunc )();

QHash< QString, BundleLibrary::Ptr > BundleLoader::loadAll(
        const QString &location )
{
    QHash< QString, BundleLibrary::Ptr > bundles;
    QDir pluginDir( location );
    if( pluginDir.exists() ) {
        QStringList entries = pluginDir.entryList();;
        for( const QString entry : entries ) {
            if( QLibrary::isLibrary( entry )) {
                BundleLibrary::Ptr blib = loadFile( entry );
                if( blib->isValid() ) {
                    bundles.insert( blib->bundle().bundleId(), blib );
                }
                else {
                    VQ_ERROR( "Quartz:Core" )
                            << "Could not load the library "
                            << entry;
                }
            }
            else {
                VQ_DEBUG( "Quartz:Core" )
                        << "Ignoring file " << entry
                        << " since its not a library";
            }
        }
    }
    else {
        VQ_ERROR( "Quartz:Core" )
                << "The plugin directory " << location << "does not exists";
    }
    return bundles;
}


BundleLibrary::Ptr BundleLoader::loadFile( const QString &filePath )
{
    BundleLibrary::Ptr blib = nullptr;
    QLibrary *library = new QLibrary( filePath, qApp );
    library->load();
    if( library->isLoaded() ) {
        PluginFunc getFunc = reinterpret_cast< PluginFunc >(
                    library->resolve( INTERFACE_FUNC_NAME ));
        if( getFunc != nullptr ) {
            BundleWrapper wrapper = getFunc();
            PluginBundle *bundle = wrapper.m_bundle;
            blib = std::make_shared< BundleLibrary >( library, bundle );
        }
    }
    return blib;
}


}
