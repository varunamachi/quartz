#include <fstream>
#include <unordered_set>

#include "../../logger/Logging.h"
#include "File.h"
#include "FSUtils.h"


namespace Vq {

Result< File > FSUtils::fileAt( const std::string &path )
{
    auto resPath = Path::create( path );
    if( ! resPath.value() ) {
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
            << "Cannot create file object, invalid path" << path
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
                << "Could not create file at " << path << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << result;
    }
    return result;
}


Result< bool > validateForCopyFile( File &srcFile,
                                    File &dstFile,
                                    bool isMove,
                                    bool force )
{
    auto result = R::success( true );
    File srcParent{ srcFile.path().parent() };
    File destParent{ dstFile.path().parent() };
    const auto op = isMove ? "File Move: " : "File Copy: ";
    if( ! srcFile.exists() ) {
        result = R::stream( false )
                << op << "Source file at " << srcFile << " does not exists"
                << R::fail;
    }
    else if( ! srcFile.isReadable() ) {
        result = R::stream( false )
                << op << "Source file at " << srcFile << " is not readable"
                << R::fail;
    }
    else if( ! destParent.exists() ) {
        result = R::stream( false )
                << op << "Destination path " << dstFile
                << " does not exist" << R::fail;
    }
    else if( ! destParent.isWritable() ) {
        result = R::stream( false )
                << op << "Destination path "
                << dstFile << " is not writable"
                << R::fail;
    }
    else if( force && dstFile.exists() && ! dstFile.isWritable() ) {
        result = R::stream( false )
                << op << "Destination file at " << dstFile
                <<  "exist and is not writable" << R::fail;
    }
    else if( srcFile.type() != File::Type::Regular ) {
        result = R::stream( false )
                << op << "Invalid source file type, operation only works for "
                         "regular files" << R::fail;
    }
    else if( isMove && srcParent.isWritable() ) {
        result = R::stream( false )
                << op << "Source file at <<  srcFile << is not writable"
                << R::fail;
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

    if( ! ( srcRes.value()  && dstRes.value() )) {
        auto error = R::stream( false )
                << "Invalid path given for copy, Source: " << psrc
                << " Destination: " << pdst << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << error;
        return error;
    }

    File srcFile{ srcRes.data() };
    File dstFile{ dstRes.data() };

    auto result = validateForCopyFile( srcFile, dstFile, false, forceCopy );
    if( forceCopy && dstFile.exists() ) {
        result = deleteFile( dstFile );
    }
    if( result ) {
        result = copyFileImpl( srcFile, dstFile, progCallback );
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

    if( ! ( srcRes.value()  && dstRes.value() )) {
        auto error = R::stream( false )
                << "Invalid path given for move, Source: " << psrc
                << " Destination: " << pdst << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << error;
        return error;
    }

    File srcFile{ srcRes.data() };
    File dstFile{ dstRes.data() };
    auto result = validateForCopyFile( srcFile, dstFile, true, forceMove );
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
    resultCallback( result );
    return result;
}


static Result< bool > validateForCopyDir(
        const File &srcDir,
        const File &dstDir,
        bool isMove,
        FSUtils::ConflictStrategy onConflict )
{
    auto op = isMove ? "Directory Move: " : "Directory Copy: ";
    auto result = R::success( true );
    File srcParent{ srcDir.path().parent() };
    File dstParent{ dstDir.path().parent() };
    //Perfrom basic validation
    if( ! ( srcParent.exists() && srcParent.isReadable() )) {
        //Parent of source is not accessable
        result = R::stream( false )
                << op << "Parent directory of source directory at "
                << srcDir << " is not accessible" << R::fail;
    }
    else if( ! srcDir.exists() ) {
        result = R::stream( false )
                << op << "Source directory at " << srcDir
                << " does not exist" << R::fail;
    }
    else if( srcDir.type() != File::Type::Dir ) {
        result = R::stream( false )
                << op << "Source file at "
                << srcDir << " is not a directory" << R::fail;
    }
    else if( ! ( dstParent.exists() && dstParent.isWritable() )) {
        result = R::stream( false )
                << op << "Parent directory of source directory at "
                << srcDir << " is not accessible" << R::fail;
    }
    else if( dstDir.exists() ) {
        if( onConflict  == FSUtils::ConflictStrategy::Stop ) {
            //The destination directory exists and the conflict policy demands
            //stoping the copy
            result = R::stream( false )
                    << op << "Destination directory at " << dstDir
                    << " already exits, stopping..." << R::fail;
        }
        else if( onConflict  != FSUtils::ConflictStrategy::Skip
                 && ! dstDir.isWritable() ) {
            //The destinatio directory exist and is not writable, this will
            //cause error if the conflict policy is not error
            result = R::stream( false )
                    << op << "Destination directory at " << dstDir << " already "
                    << "exits and is not writable..." << R::fail;
        }
    }
    else if( isMove && ! ( srcDir.isWritable() && srcParent.isWritable() )) {
        result = R::stream( false )
                << op << "The source directory at " << dstDir
                << "is not writable (hence cannot be deleted)" << R::fail;
    }
    if( ! result.value() ) {
        VQ_ERROR( "Vq:Core:FS" ) << result;
    }
    return result;
}

Result< bool > FSUtils::copyDirectory( const std::string &srcStrPath,
                                       const std::string &dstStrPath,
                                       ConflictStrategy conflictPolicy ,
                                       FSUtils::BoolResultFunc resultCallback,
                                       DirCopyProgFunc progCallback )
{
    auto srcPathRes = Path::create( srcStrPath );
    auto dstPathRes = Path::create( dstStrPath );

    //First check if paths are properly formed
    if( ! ( srcPathRes.value() && dstPathRes.value() )) {
        auto stream = std::move( R::stream( false ) << "Dir Copy: " );
        if( ! srcPathRes.value() ) {
            stream << "Invalid source path " << srcStrPath << " given";
        }
        else {
            stream << "Invalid destination path " << srcStrPath << " given";
        }
        auto error = stream << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << error;
        return error;
    }
    const auto &srcPath = srcPathRes.data();
    const auto &destPath = dstPathRes.data();
    File srcDir{ srcPathRes.data() };
    File dstDir{ dstPathRes.data() };

    auto result = validateForCopyDir( srcDir, dstDir, false, conflictPolicy );
    if( ! result ) {
        return result;
    }

    //Ready to Copy!!
    auto flistRes = listFiles( srcDir, [ & ]( const File &file ) -> bool
    {
        auto result = ( file.type() == File::Type::Regular
                        || file.type() == File::Type::Link );
        return result;
    });

    if( flistRes.value() ) {
        auto &fileList = flistRes.data();
        std::size_t numCompleted = 0;
        for( const auto & file : fileList ) {
            auto relative = file.path().relativeTo( srcPath ).data();
            auto destFilePath = destPath.appended( relative );
            //Take the difference between the paths and prepend it
            File destFile{ destFilePath };
            if( destFile.exists() ) {
                //Apply conflict resolution policy
                if( conflictPolicy  == ConflictStrategy::Merge
                        || conflictPolicy  == ConflictStrategy::Skip ) {
                    VQ_WARN( "Vq:Core:FS" )
                            << "File " << destFile
                            << " already exists, skipping.";
                    continue;
                }
                else if( conflictPolicy == ConflictStrategy::Overwrite ) {
                    VQ_WARN( "Vq:Core:FS" )
                            << "File " << destFile
                            << " already exists, Deleting!!.";
                    auto delRes = deleteFile( destFile );
                    if( ! delRes ) {
                        result = R::failure( false, std::move( delRes ));
                        break;
                    }
                }
                else if( conflictPolicy == ConflictStrategy::Stop ) {
                    VQ_WARN( "Vq:Core:FS" )
                            << "File " << destFile
                            << " already exists, stopping copy!!";
                    //revert?
                    break;
                }
            }
            auto cpFileRes = copyFileImpl( file, destFile, nullptr );
            if( ! cpFileRes ) {
                VQ_WARN( "Vq:Core:FS" )
                        << "Could not copy file " << file
                        << ": " << cpFileRes << " Skipping...";
            }
            if( progCallback != nullptr &&
                    ! progCallback( fileList.size(),
                                    numCompleted,
                                    file,
                                    destFile )) {
                //user requested cancel
            }
            ++ numCompleted;
        }
        VQ_INFO( "Vq:Core:FS" )
                << "Copied " << numCompleted << " files from ";
    }
    else {
        //error
    }
    if( resultCallback != nullptr ) {
        resultCallback( result );
    }
    return result;
}


Result< bool > FSUtils::moveDirectory( const std::string &srcStrPath,
                                       const std::string &dstStrPath,
                                       ConflictStrategy conflictPolicy,
                                       FSUtils::BoolResultFunc resultCallback,
                                       DirCopyProgFunc progCallback )
{
    auto srcPathRes = Path::create( srcStrPath );
    auto dstPathRes = Path::create( dstStrPath );

    //First check if paths are properly formed
    if( ! ( srcPathRes.value() && dstPathRes.value() )) {
        auto stream = std::move( R::stream( false ) << "Dir Copy: " );
        if( ! srcPathRes.value() ) {
            stream << "Invalid source path " << srcStrPath << " given";
        }
        else {
            stream << "Invalid destination path " << srcStrPath << " given";
        }
        auto error = stream << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << error;
        return error;
    }
    const auto &srcPath = srcPathRes.data();
    const auto &destPath = dstPathRes.data();
    File srcDir{ srcPathRes.data() };
    File dstDir{ dstPathRes.data() };

    auto result = validateForCopyDir( srcDir, dstDir, true, conflictPolicy );
    if( ! result ) {
        return result;
    }
    if( resultCallback != nullptr ) {
        resultCallback( result );
    }
    return result;
}

}
