#include <fstream>

#include "../../logger/Logging.h"
#include "File.h"
#include "FSUtils.h"


namespace Vq {

Result< File > FSUtils::fileAt( const std::string &path )
{
    auto resPath = Path::create( path );
    if( ! resPath ) {
        return R::failure< File >( File{ }, std::move( resPath ));
    }
    File file{ resPath.data() };
    return R::success< File >( file );

}



Result< File > FSUtils::fileAt( const Path &path )
{
    if( path.isValid() ) {
        return R::success< File >( File{ path });
    }
    auto error = R::stream( File{ })
            << "Cannot create file object, invalid path" << path.toString()
            << " given" << R::fail;
    VQ_ERROR( "Vq:Core:FS" ) << error;
    return error;
}


Result< bool > FSUtils::createRegularFile( const File &file )
{
    const auto &path = file.path();
    File parent{ path.parent() };
    if( file.exists() ) {
        return R::success( true );
    }
    else if( ! parent.exists() ) {
        auto error = R::stream( false )
                << "Could not find the directory " << parent.path().fileName()
                << "where the file is to be created." << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << error;
        return error;
    }
    else if( ! parent.isWritable() ) {
        auto error = R::stream( false )
                << "The directory " << parent.path().fileName()
                << "where the file is to be created is not writable" << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << error;
        return error;
    }
    std::ofstream fstr( path.toString() );
    auto result = R::success( true );
    if( ! fstr.is_open() ) {
        result = R::stream( false )
                << "Could not create file at " << path.toString() << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << result;
    }
    return result;
}

Result< bool > FSUtils::copyFile( const std::string &psrc,
                                  const std::string &pdst,
                                  const bool forceCopy,
                                  FSUtils::BoolResultFunc resultCallback,
                                  ProgressFunction progCallback)
{
    auto srcRes = Path::create( psrc );
    auto dstRes = Path::create( pdst );

    auto dstParent = dstRes.data().parent();
    if( ! ( srcRes  && dstRes )) {
        auto error = R::stream( false )
                << "Invalid path given for copy, Source: " << psrc
                << " Destination: " << pdst << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << error;
        return error;
    }

    File srcFile{ srcRes.data() };
    File dstFile{ dstRes.data() };
    File parentFile{ dstParent };
    auto result = R::success( true );
    if( ! srcFile.exists() ) {
        result = R::stream( false )
                << "File Copy: Source file at " << psrc << " does not exists"
                << R::fail;
    }
    else if( ! srcFile.isReadable() ) {
        result = R::stream( false )
                << "File Copy: Source file at " << psrc << " is not readable"
                << R::fail;
    }
    else if( ! parentFile.exists() ) {
        result = R::stream( false )
                << "File Copy: Destination path " << pdst << " does not exist "
                << R::fail;
    }
    else if( ! parentFile.isWritable() ) {
        result = R::stream( false )
                << "File Copy: Destination path " << pdst << " is not writable"
                << R::fail;
    }
    else if( forceCopy && srcFile.exists() && ! srcFile.isWritable() ) {
        result = R::stream( false )
                << "File Copy: Destination file at " << pdst
                <<  "exist and is not writable" << R::fail;
    }
    else if( srcFile.type() != File::Type::Regular ) {
        result = R::stream( false )
                << "Invalid source file type, copy only works for regular files"
                << R::fail;
    }
    else {
        if( dstFile.exists() ) {
            result = deleteFile( dstFile );
        }
        if( result ) {
            result = copyFileImpl( srcFile, dstFile, progCallback );
        }
    }
    resultCallback( result );
    return result;
}


Result< bool > FSUtils::moveFile( const std::string &psrc,
                                  const std::string &pdst,
                                  bool forceMove,
                                  FSUtils::BoolResultFunc resultCallback,
                                  ProgressFunction progCallback )
{
    auto srcRes = Path::create( psrc );
    auto dstRes = Path::create( pdst );

    if( ! ( srcRes  && dstRes )) {
        auto error = R::stream( false )
                << "Invalid path given for move, Source: " << psrc
                << " Destination: " << pdst << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << error;
        return error;
    }

    File srcFile{ srcRes.data() };
    File dstFile{ dstRes.data() };
    File srcParent{ srcRes.data().parent() };
    File dstParent{ dstRes.data().parent() };
    auto result = R::success( true );
    if( ! srcFile.exists() ) {
        result = R::stream( false )
                << "File Move: Source file at " << psrc << " does not exists"
                << R::fail;
    }
    else if( ! srcParent.isReadable() || ! srcFile.isReadable() ) {
        result = R::stream( false )
                << "File Move: Source file at " << psrc << " is not readable"
                << R::fail;
    }
    else if( ! srcParent.isWritable() || ! srcFile.isWritable() ) {
        result = R::stream( false )
                << "File Move: Source file at " << psrc << " is not writable"
                << " hence cannot be move" << R::fail;
    }
    else if( ! dstParent.exists() ) {
        result = R::stream( false )
                << "File Move: Destination path " << pdst << " does not exist "
                << R::fail;
    }
    else if( ! dstParent.isWritable() ) {
        result = R::stream( false )
                << "File Move: Destination path " << pdst << " is not writable"
                << R::fail;
    }
    else if( forceMove && srcFile.exists() && ! srcFile.isWritable() ) {
        result = R::stream( false )
                << "File Move: Destination file at " << pdst
                <<  "exist and is not writable" << R::fail;
    }
    else if( srcFile.type() != File::Type::Regular ) {
        result = R::stream( false )
                << "Invalid source file type, copy only works for regular files"
                << R::fail;
    }
    else {
        if( dstFile.exists() ) {
            result = deleteFile( dstFile );
        }
        if( result ) {
            VQ_DEBUG( "Vq:Core:FS" )
                    << "File Move: copying file "  << psrc << " to " << pdst;
            result = copyFileImpl( srcFile, dstFile, progCallback );
            if( result ) {
                VQ_DEBUG( "Vq:Core:FS" )
                        << "File Move: deleting file "  << psrc
                        << " after copying it to " << pdst;
                result = deleteFile( srcFile );
            }
        }
    }
    resultCallback( result );
    return result;
}


}
