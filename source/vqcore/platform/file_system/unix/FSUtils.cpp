
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/sendfile.h>
#include <sys/stat.h>

#include "../../../common/ScopedOperation.h"
#include "../../../logger/Logging.h"
#include "../FSUtils.h"

namespace Vq {

Result< bool > FSUtils::deleteFile( const File &file )
{
    const auto &path = file.path();
    File parent{ path.parent() };
    if( ! file.exists() ) {
        auto error = R::stream( false )
                << "Could not delete file at " << path
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
                << "Could not delete file at " << path
                << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << result;
    }
    return result;
}


static Result< bool > list( const File &dir,
                            FSUtils::FilterFunction filter,
                            VQ_OUT FSUtils::FileList &filesOut )
{
    auto result = R::success( true );
    if( ! dir.exists() ) {
        result = R::stream( false )
                << "List files: directory at " << dir
                << " does not exist" << R::fail;
    }
    else if( dir.type() != File::Type::Dir ) {
        result = R::stream( false )
                << "List files: File at " << dir
                << " is not a directory" << R::fail;
    }
    else if( ! dir.isReadable() ) {
        result = R::stream( false )
                << "List files: directory at " << dir
                << " is not readable" << R::fail;
    }
    if( ! result ) {
        VQ_ERROR( "Vq:Core:FS" ) << result;
        return result;
    }

    auto &path = dir.path();
    auto dirp = ::opendir( dir.path().toString().c_str() );
    struct dirent *dirPtr;
    if( dirp != nullptr ) {
        //should it be readdir64?
        while(( dirPtr = ::readdir( dirp )) != nullptr ) {
            auto newPath = path.pathOfChild( dirPtr->d_name ).data();
            File newFile{ newPath };
            if( newFile.type() == File::Type::Dir ) {
                filesOut.emplace_back( newFile );
                auto res = list( newFile, filter, filesOut );
                if( ! res ) {
                    //Or we could return
                    continue;
                }
            }
            else {
                if( filter == nullptr || filter( newFile )) {
                    filesOut.emplace_back( std::move( newFile ));
                }
            }
        }
    }
    else {
        result = R::stream( false, errno )
                << "Failed to stat the directory at " << dir
                << R::fail;
    }
    return result;
}


Result< FSUtils::FileList > FSUtils::listFiles(
        const File &dir,
        FSUtils::FilterFunction filter,
        std::function< void( Result< FileList >)> resultCallback )
{
    FileList files;
    auto rz = list( dir, filter, files );
    auto result = R::success< FileList >( files );
    if( ! rz ) {
        result = R::failure< FileList >( files, std::move( rz ));
    }
    resultCallback( result );
    return result;
}

Result< bool > FSUtils::copyFileImpl( const File &src,
                                      const File &dst,
                                      ProgressFunction progCallback )
{
    auto destParentPath = dst.path().parent();
    //Create directories in destination path if they dont exist
    auto dirCreateRes = createDirecties( destParentPath.toString() );
    if( ! dirCreateRes ) {
        auto err = R::stream( false )
                << "Could not copy " << src << " to "
                << dst << " due to error while creating "
                << " directories in destination path, Error: "
                << dirCreateRes.reason() << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << err;
        return err;
    }
    auto srcFd = ::open( src.path().toString().c_str(), O_RDONLY);
    struct stat srcStat;
    ::fstat ( srcFd, &srcStat );
    auto dstFd = ::open( dst.path().toString().c_str(),
                         O_WRONLY | O_CREAT,
                         srcStat.st_mode );
    if( srcFd == 0 || dstFd == 0 ) {
        auto error = R::stream( false )
                << "Failed to open "
                << ( srcFd == 0 ? "source" : "destination")
                << ( srcFd == 0 ? src
                                : dst ) << " file" << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << error;
        return error;
    }
    AT_SCOPE_EXIT( close( srcFd ));
    AT_SCOPE_EXIT( close( dstFd ));
    auto result = R::success( true );
    if( progCallback == nullptr ) {
        //if progress information is not required we use the kernel mode copy
        /* Stat the input file to obtain its size. */
        //Open destination file, with same permission as the source
        ::off_t offset;
        auto retVal = sendfile( srcFd,
                                dstFd,
                                &offset,
                                static_cast< std::size_t >( srcStat.st_size ));
        if( retVal == -1 ) {
             result = R::stream( false, errno )
                     << "Copy File: sendfile failed, src: "
                     << src << " dst: "
                     << dst << R::fail;
        }

    }
    else {
        static const std::size_t BUFFER_SIZE = ( 32 * 1024 );
        static char buffer[ BUFFER_SIZE ];
        std::size_t totalCopied = 0;
        while( true ) {
            auto rdSz = ::read( srcFd, buffer, BUFFER_SIZE );
            if( rdSz == 0 ) {
                break;
            }
            auto wrSz = ::write( dstFd,
                                 buffer,
                                 static_cast< std::size_t>( rdSz ));
            if( wrSz != rdSz ) {
                result = R::stream( false, errno )
                        << "File Copy: Writing to destination file at "
                        << dst << " failed" << R::fail;
                VQ_ERROR( "Vq:Core:FS" ) << result;
                break;
            }
            totalCopied += static_cast< std::size_t >( rdSz );
            auto progress = static_cast< std::uint8_t>(
                        src.fileSize().data() / totalCopied );
            progCallback( progress );
        }
    }
    return result;
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
                                   const bool force )
{
    return R::failure( false );
}


}
