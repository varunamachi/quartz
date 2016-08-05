
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


}
