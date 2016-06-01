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

    static std::vector< std::string > split( const std::string &orig,
                                             const std::string &delim,
                                             const std::size_t &maxSplits );

private:

};

}
