
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



std::vector< std::string > StringUtils::splitFromStart(
        const std::string &orig,
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
        if( pos == std::string::npos ) {
            prev = 0;
            break;
        }
        auto token = orig.substr( prev, pos - prev );
        tokens.emplace_back( std::move( token ));
        ++ numSplits;
        prev = pos + delim.size();
    } while( pos != std::string::npos
             && numSplits < maxSplits
             && prev < orig.size() );

    if( numSplits < maxSplits && prev < orig.length() ) {
        auto token = orig.substr( prev, std::string::npos );
        tokens.emplace_back( std::move( token ));
    }
    return tokens;
}


std::vector< std::string > StringUtils::splitFromEnd(
        const std::string &orig,
        const std::string &delim,
        const std::size_t &maxSplits )
{
    std::vector< std::string > tokens;
    if( maxSplits == 0 ) {
        return tokens;
    }
    auto pos  = orig.size();
    auto prev = orig.size();
    std::size_t numSplits = 0;
    do {
        pos = orig.find_last_of( delim, prev );
        if( pos == std::string::npos ) {
            prev = 0;
            break;
        }
        auto token = orig.substr( pos, prev - pos );
        tokens.emplace_back( std::move( token ));
        ++ numSplits;
        prev = pos - delim.size();
    } while( numSplits < maxSplits && prev > 0 );

    if( numSplits < maxSplits && prev > 0 ) {
        auto token = orig.substr( prev, std::string::npos );
        tokens.emplace_back( std::move( token ));
    }
    return tokens;
}


bool StringUtils::endsWith( const std::string &str, const std::string &test )
{
    bool result = false;
    if( ! test.empty() && str.size() >= test.size() ) {

    }
    return result;
}


bool StringUtils::startsWith( const std::string &str, const std::string &test )
{
    return false;
}


bool StringUtils::contains( const std::string &str, const std::string &test )
{
    return false;
}

}
