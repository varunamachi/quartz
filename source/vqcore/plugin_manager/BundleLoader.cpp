

#include "../logger/Logging.h"
#include "../platform/file_system/FSUtils.h"
#include "../platform/file_system/File.h"
#include "../platform/file_system/Path.h"
#include "../platform/shared_library/SharedLibrary.h"
#include "BundleLibrary.h"
#include "PluginBundleInterface.h"

#include "BundleLoader.h"

namespace Vq {


static const char * INTERFACE_FUNC_NAME = "pluginBundle";
typedef BundleWrapper ( *PluginFunc )();


Result< BundleMap > BundleLoader::loadAll( const std::string &location )
{
    File pluginDir( Path::create( location ));
    if( pluginDir.type() == File::Type::Dir ) {
        auto result = R::stream( BundleMap{ } )
                << "The plugin load location is not a "
                   "directory " << location << R::fail;
        VQ_ERROR( "Vq:Ext" ) << result;
        return result;
    }
    BundleMap bundleMap;
    auto files = FSUtils::listFiles( pluginDir,
                                     []( const File &file ) -> bool {
        const auto &ext = file.path().extension();
        auto result = file.type() == File::Type::Regular
                && ( ext == "so"
                     || ext == "dll"
                     || ext == "dylib" );
        return result;
    });
    for( const auto &file : files.data() ) {
        auto libRes = loadFile( file.path().toString() );
        if( libRes.value() ) {
            bundleMap.emplace( libRes.data()->bundle()->bundleId(),
                               libRes.data() );
        }
    }
    return R::success( std::move( bundleMap ));
}


Result< BundleLibraryPtrUq > BundleLoader::loadFile(
        const std::string &filePath )
{
    auto result = R::failure( BundleLibraryPtrUq{ nullptr }, "Unknown error" );
    auto lib = std::make_unique< SharedLibrary >( filePath );
    auto ldRes = lib->load();
    if( ldRes ) {
        auto funcRes = lib->resolve( INTERFACE_FUNC_NAME );
        if( funcRes.value() ) {
            auto func = funcRes.data();
            auto bundleWrapper = func.call< BundleWrapper >();
            auto bundle = bundleWrapper.theBundle;
            auto bundleLib = std::make_unique< BundleLibrary >(
                        std::move( lib ),
                        std::unique_ptr< PluginBundle >( bundle ));
            result = R::success( std::move( bundleLib ));
        }
        else {
            result = R::stream( BundleLibraryPtrUq{ }, funcRes.errorCode() )
                    << "Could not resolve the plugin initializer function for "
                       "library at " << filePath << R::fail;
            VQ_ERROR( "Vq:Ext" ) << result;
        }
    }
    else {
        result = R::stream( BundleLibraryPtrUq{ }, ldRes.errorCode() )
                << "Failed to load plugin library at " << filePath << " - "
                << ldRes.reason() << R::fail;
        VQ_ERROR( "Vq:Ext" ) << result;
    }
    return result;
}


}
