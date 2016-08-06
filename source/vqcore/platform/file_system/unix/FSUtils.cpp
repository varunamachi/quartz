
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

#include "../../../logger/Logging.h"
#include "../FSUtils.h"

namespace Vq {

Result< bool > FSUtils::deleteFile( const File &file )
{
    const auto &path = file.path();
    File parent{ path.parent() };
    if( ! file.exists() ) {
        auto error = R::stream( false )
                << "Could not delete file at " << path.toString()
                << ", file does not exist" << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << error;
        return error;
    }
    else if( ! parent.isWritable() ) {
        auto error = R::stream( false )
                << "Parent of file " << parent.path().fileName()
                << "that is to be deleted is not writable" << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << error;
        return error;
    }
    auto result = R::success( true );
    if( unlink( path.toString().c_str() ) != 0 )  {
        result = R::stream( false, errno )
                << "Could not delete file at " << path.toString()
                << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << result;
    }
    return result;
}



Result< FSUtils::FileList > FSUtils::listFiles(
        const File &dir,
        FSUtils::FilterFunction filter,
        std::function< void( Result< FileList >)> resultCallback )
{
    auto result = R::success< FileList >( FileList{} );
    if( ! dir.exists() ) {
        result = R::stream< FileList >( FileList{} )
                << "List files: directory at " << dir.path().toString()
                << " does not exist" << R::fail;
    }
    else if( dir.type() != File::Type::Dir ) {
        result = R::stream< FileList >( FileList{} )
                << "List files: File at " << dir.path().toString()
                << " is not a directory" << R::fail;
    }
    else if( ! dir.isReadable() ) {
        result = R::stream< FileList >( FileList{} )
                << "List files: directory at " << dir.path().toString()
                << " is not readable" << R::fail;
    }
    if( ! result ) {
        VQ_ERROR( "Vq:Core:FS" ) << result;
        resultCallback( result );
        return result;
    }

    auto &path = dir.path();
    auto dirp = ::opendir( dir.path().toString().c_str() );
    struct dirent *dirPtr;
    if( dirp != nullptr ) {
        FileList files;
        //should it be readdir64?
        while(( dirPtr = ::readdir( dirp )) != nullptr ) {
            auto newPath = path.pathOfChild( dirPtr->d_name ).data();
            File newFile{ newPath };
            if( newFile.type() == File::Type::Dir ) {
                files.emplace_back( newFile );
                //TODO do a recursive call, but this needs file list to be taken
                // as parameter. Better create a function that calls the
                // recursive function.
                //
                //listFiles( newFile, filter, resultCallback );
            }
            else {
                if( filter == nullptr || filter( newFile )) {
                    files.emplace_back( std::move( newFile ));
                }
            }
        }
    }
    else {
        result = R::stream< FileList >( FileList{}, errno )
                << "Failed to stat the directory at " << dir.path().toString()
                << R::fail;
    }
    return result;
}



Result< bool > FSUtils::copyFile( const std::string &srcPath,
                                  const std::string &dstPath,
                                  FSUtils::BoolResultFunc resultCallback,
                                  ProgressFunction progCallback)
{
    return R::failure( false );
}



Result< bool > FSUtils::moveFile( const std::string &srcPath,
                                  const std::string &dstPath,
                                  FSUtils::BoolResultFunc resultCallback,
                                  ProgressFunction progCallback )
{
    return R::failure( false );
}



Result< bool > FSUtils::copyDirectory( const std::string &srcPath,
                                       const std::string &dstPath,
                                       FSUtils::BoolResultFunc resultCallback,
                                       DetailedProgressFunc progCallback )
{
    return R::failure( false );
}



Result< bool > FSUtils::moveDirectory( const std::string &srcPath,
                                       const std::string &dstPath,
                                       FSUtils::BoolResultFunc resultCallback,
                                       DetailedProgressFunc progCallback )
{
    return R::failure( false );
}



Result< bool > FSUtils::createDirecties( const std::string &path )
{
    return R::failure( false );
}



Result< bool > FSUtils::createSoftLink( const std::string &targetPath,
                                        const std::string &linkPath )
{
    return R::failure( false );
}



Result< bool > FSUtils::deleteDir( const std::string &path,
                                   const bool force,
                                   const bool recursive )
{
    return R::failure( false );
}


}
