#pragma once

#include <string>
#include <vector>

#include "Macros.h"
#include "Result.h"

namespace Vq {

class StringUtils
{
public:
    VQ_MAKE_STATIC( StringUtils );

    static std::vector< std::string > split( const std::string &orig,
                                             const std::string &delim );

    static std::vector< std::string > splitFromStart(
            const std::string &orig,
            const std::string &delim,
            const std::size_t &maxSplits );

    static std::vector< std::string > splitFromEnd(
            const std::string &orig,
            const std::string &end,
            const std::size_t &maxSplits );

    static bool endsWith( const std::string &str,
                          const std::string &test );

    static bool startsWith( const std::string &str,
                            const std::string &test );

    static bool contains( const std::string &str,
                          const std::string &test );

    bool isAsciiChar( char ch );

private:

};

}
