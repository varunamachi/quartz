
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


std::string Path::toString() const
{
    std::stringstream stream;
    for( const auto & cmp : components() ) {
        stream << cmp << SEPERATOR;
    }
    auto path = stream.str();
    return path;
}


Result< Path & > Path::mergeWith( const Path &other )
{
    auto isAbs = false;
    auto result = R::success< Path & >( *this );
    if( this->isAbsolute() && other.isAbsolute() ) {
        auto &main = STLUtils::largestOf( components(), other.components() );
        auto &slv = STLUtils::smallestOf( components(), other.components() );
        auto mit = std::cbegin( main );
        for( auto sit = std::cbegin( slv ); sit != std::cend( slv ); ++ sit ) {
            if( *sit != *mit ) {
                result = R::stream< Path & >( *this )
                        << "Failed to merge path, size given paths are absolute"
                           "and are different withing the merge range"
                        << R::fail;
                VQ_ERROR( "Vq:Core:FS" ) << result;
                break;
            }
            ++ mit;
        }
        if( result && ( &main == &( other.components() ))) {
            for( ; mit != std::cend( main ); ++ mit ) {
                this->mutableComponents().push_back( *mit );
            }
        }
        return result;
    }
    else if( this->isAbsolute() ) {
        auto mit = std::cbegin( this->components() );
        auto oit = std::cbegin( other.components() );
        auto matchStarted = false;
        for( ; mit != std::cend( this->components() ); ++ mit ) {
            if( *mit == *oit ) {
                ++ oit;
                matchStarted = true;
            }
            else if( matchStarted && *mit != *oit ) {
                oit = std::cbegin( other.components() );
                matchStarted = false;
            }
        }
        for( ; oit != std::cend( other.components()); ++ oit ) {
            this->mutableComponents().push_back( *oit );
        }
    }
    else if( other.isAbsolute() ) {

    }
    else {

    }
}


Result< Path & > Path::relativeTo( const Path & other )
{

}

}
