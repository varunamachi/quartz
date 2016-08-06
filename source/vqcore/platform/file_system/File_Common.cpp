

#include "File.h"
#include "Path.h"

namespace Vq {

File::File( const std::string &path )
    : File( Path::create( path ).data() )
{

}

}
