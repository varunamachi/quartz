
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

    return R::failure( false );
}



Result< bool > FSUtils::deleteFile( const File &file )
{
    return R::failure( false );
}



Result< FSUtils::FileList > FSUtils::listFiles(
        const File &dir,
        FSUtils::FilterFunction filter,
        std::function< void( Result< FileList >)> resultCallback,
        DetailedProgressFunc progFunc )
{
    return R::failure< FSUtils::FileList >();
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
