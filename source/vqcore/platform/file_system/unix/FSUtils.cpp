
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


static Result< bool > list( const File &dir,
                            FSUtils::FilterFunction filter,
                            VQ_OUT FSUtils::FileList &filesOut )
{
    auto result = R::success( true );
    if( ! dir.exists() ) {
        result = R::stream( false )
                << "List files: directory at " << dir.path().toString()
                << " does not exist" << R::fail;
    }
    else if( dir.type() != File::Type::Dir ) {
        result = R::stream( false )
                << "List files: File at " << dir.path().toString()
                << " is not a directory" << R::fail;
    }
    else if( ! dir.isReadable() ) {
        result = R::stream( false )
                << "List files: directory at " << dir.path().toString()
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
                << "Failed to stat the directory at " << dir.path().toString()
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
                << ( srcFd == 0 ? src.path().toString()
                                : dst.path().toString() ) << " file" << R::fail;
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
                     << src.path().toString() << " dst: "
                     << dst.path().toString() << R::fail;
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
                        << dst.path().toString() << " failed" << R::fail;
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


Result< bool > FSUtils::copyDirectory( const std::string &srcStrPath,
                                       const std::string &dstStrPath,
                                       ConflictStrategy conflictStrategy,
                                       FSUtils::BoolResultFunc resultCallback,
                                       DetailedProgressFunc progCallback )
{
    auto srcPathRes = Path::create( srcStrPath );
    auto dstPathRes = Path::create( dstStrPath );

    //First check if paths are properly formed
    if( ! ( srcPathRes && dstPathRes )) {
        auto stream = std::move( R::stream( false ) << "Dir Copy: " );
        if( ! srcPathRes ) {
            stream << "Invalid source path " << srcStrPath << " given";
        }
        else {
            stream << "Invalid destination path " << srcStrPath << " given";
        }
        auto error = stream << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << error;
        return error;
    }


    File srcDir{ srcPathRes.data() };
    File dstDir{ dstPathRes.data() };
    File srcParent{ srcDir.path().parent() };
    File dstParent{ dstDir.path().parent() };

    auto result = R::success( true );
    //Perfrom basic validation
    if( ! ( srcParent.exists() && srcParent.isReadable() )) {
        //Parent of source is not accessable
    }
    else if( ! srcDir.exists() ) {
        //The source directory does not exist
    }
    else if( srcDir.type() != File::Type::Dir ) {
        //Source is not a directory
    }
    else if( ! ( dstParent.exists() && dstParent.isWritable() )) {
        //destination is parent is not writable
    }
    else if( dstDir.exists() ) {
        if( conflictStrategy == ConflictStrategy::Stop ) {
            //The destination directory exists and the conflict policy demands
            //stoping the copy
        }
        else if( conflictStrategy != ConflictStrategy::Skip
                 && ! dstDir.isWritable() ) {
            //The destinatio directory exist and is not writable, this will
            //cause error if the conflict policy is not error
        }
    }

    //Ready to Copy!!
    auto flistRes = listFiles( srcDir );
    if( flistRes ) {
        //iterate and call file copy
        //if conflict occurs use the conflict policy
        //once all are copied, delete the copied file and not the skipped ones
    }
    else {
        //error
    }
    return result;
}



Result< bool > FSUtils::moveDirectory( const std::string &srcPath,
                                       const std::string &dstPath,
                                       ConflictStrategy conflictStrategy,
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
                                   const bool force )
{
    return R::failure( false );
}


}
