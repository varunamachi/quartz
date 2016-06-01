
#include "StringUtils.h"

namespace Vq {

std::vector< std::string > StringUtils::split( const std::string &orig,
                                               const std::string &delim )
{
    std::vector< std::string > tokens;
    std::size_t prev = 0;
    std::size_t pos  = 0;
    do{
        pos = orig.find_first_of( delim, prev );
        if( pos > prev ) {
            auto token = orig.substr( prev, pos - prev );
            tokens.emplace_back( std::move( token ));
        }
        prev = pos + 1;
    } while( pos != std::string::npos );

    if( prev < orig.length() ) {
        auto token = orig.substr( prev, std::string::npos );
        tokens.emplace_back( std::move( token ));
    }
    return tokens;
}



std::vector< std::string > StringUtils::split( const std::string &orig,
                                               const std::string &delim,
                                               const std::size_t &maxSplits )
{
    std::vector< std::string > tokens;
    if( maxSplits == 0 ) {
        return tokens;
    }
    std::size_t prev = 0;
    std::size_t pos  = 0;
    std::size_t numSplits = 0;
    do{
        pos = orig.find_first_of( delim, prev );
        if( pos > prev ) {
            auto token = orig.substr( prev, pos - prev );
            tokens.emplace_back( std::move( token ));
            ++ numSplits;
        }
        prev = pos + 1;
    } while( pos != std::string::npos && numSplits < maxSplits );

    if( numSplits < maxSplits && prev < orig.length() ) {
        auto token = orig.substr( prev, std::string::npos );
        tokens.emplace_back( std::move( token ));
    }
    return tokens;
}


}
