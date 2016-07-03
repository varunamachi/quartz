

#include "../logger/Logging.h"
#include "../platform/file_system/FSUtils.h"
#include "../platform/file_system/File.h"
#include "../platform/file_system/Path.h"
#include "../platform/shared_library/SharedLibrary.h"
#include "BundleLibrary.h"
#include "PluginBundleInterface.h"

#include "BundleLoader.h"

namespace Vq {


const char * INTERFACE_FUNC_NAME = "pluginBundle";
typedef BundleWrapper ( *PluginFunc )();


Result< BundleMap > BundleLoader::loadAll( const std::string &location )
{
    auto result = Result< BundleMap >::failure( BundleMap{ },
                                                "Unknown error" );
    File pluginDir(( Path( location )));
    if( pluginDir.type().data() == File::Type::Dir ) {
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
            if( libRes.result() ) {
                bundleMap.emplace( libRes.data()->bundle()->bundleId(),
                                   libRes.data() );
            }
        }
        result = Result< BundleMap >::success( bundleMap );
    }
    else {
        VQ_ERROR( "Vq:Ext" ) << "The plugin load location is not a "
                                "directory " << location;
        result = Result< BundleMap >::failure(
                    BundleMap{ },
                    "The plugin load location is not a directory ");
    }
    return result;
}


Result< BundleLibraryPtrUq > BundleLoader::loadFile(
        const std::string &filePath )
{
    auto result = Result< BundleLibraryPtrUq >::failure(
                nullptr,
                "Unknown error" );
    auto lib = std::make_unique< SharedLibrary >( filePath );
    auto ldRes = lib->load();
    if( ldRes ) {
        auto funcRes = lib->resolve( INTERFACE_FUNC_NAME );
        if( funcRes ) {
            auto func = funcRes.data();
            auto bundleWrapper = reinterpret_cast< BundleWrapper *>(
                        func() );
            auto bundle = bundleWrapper->theBundle;
            auto bundleLib = std::make_unique< BundleLibrary >(
                        std::move( lib ),
                        std::unique_ptr< PluginBundle >( bundle ));
            result = Result< BundleLibraryPtrUq >::success(
                        std::move( bundleLib ));
        }
    }
    else {
        VQ_ERROR( "Vq:Ext" ) << "Failed to load file at " << filePath;
    }
    return result;
}


}
