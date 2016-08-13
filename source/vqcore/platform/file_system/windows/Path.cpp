
#include "../../../common/StringUtils.h"
#include "../../../common/STLUtils.h"
#include "../../../logger/Logging.h"
#include "../Path.h"

namespace Vq
{

const std::string Path::SEPERATOR( "\\" );

Result< Path > Path::create( const std::string &strPath )
{
    auto compRes = parse( strPath );
    if( compRes ) {
        auto absolute = false;
        if( StringUtils::isAsciiChar( strPath[ 0 ]) && strPath[ 1 ] == ':' ) {
            absolute = true;
        }
        return R::success( Path{ std::move( compRes.data() ), absolute });
    }
    return R::failure( Path{}, compRes.reason() );
}


Result< std::vector< std::string >> Path::parse( const std::string &strPath )
{
    std::vector< std::string > comps;
    if( strPath.empty() ) {
        auto error = R::stream( comps )
                << "The given path string is empty"
                << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << error;
        return  error;
    }
    auto it = std::begin( strPath );
    std::stringstream stream;
    char prev = 0;
    char cur  = 0;
    for( ; it != std::end( strPath ); ++ it ) {
        cur = *it;
        if( cur == '/' || cur == '\\' ) {
            auto comp = stream.str();
            if( ! comp.empty() ) {
                comps.emplace_back( std::move( comp ));
                stream.str( "" );
                stream.clear();
            }
        }
        else {
            stream << cur;
        }
        prev = cur;
    }
    return R::success< std::vector< std::string >>( comps );
}



bool Path::isValid() const
{
    bool result = ! components().empty();
    return result;
}


std::string Path::collapse() const
{
    std::stringstream stream;
    for( const auto & cmp : components() ) {
        stream << cmp << SEPERATOR;
    }
    auto path = stream.str();
    return path;
}

}
