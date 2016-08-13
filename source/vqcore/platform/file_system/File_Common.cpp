

#include "File.h"
#include "Path.h"

namespace Vq {

File::File( const std::string &path )
    : File( Path::create( path ).data() )
{

}


std::ostream & operator<<( std::ostream &stream, const File &file )
{
    stream << file;
    return stream;
}

}
