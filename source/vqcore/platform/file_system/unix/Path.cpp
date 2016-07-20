#include "../../../common/StringUtils.h"
#include "../Path.h"


namespace Vq {

const std::string Path::SEPERATOR( "/" );

Result< Path > Path::create( const std::string &strPath )
{
    return R::success< Path >( Path{ parse( strPath ).data(), true });
}


Result< std::vector< std::string >> Path::parse( const std::string &strPath )
{
    return R::success( std::vector< std::string > { "" });
}


bool Path::isValid() const
{
    bool result = isAbsolute() || ( ! components().empty() );
    return result;
}


std::string Path::toString() const
{
    std::stringstream stream;
    if( isAbsolute()  )  {
        stream << "/";
    }
    for( const auto & cmp : components() ) {
        stream << cmp << SEPERATOR;
    }
    auto path = stream.str();
    return path;
}

}
