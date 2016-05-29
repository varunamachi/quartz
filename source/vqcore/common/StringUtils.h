#pragma once

#include <string>
#include <vector>

#include "Macros.h"
#include "Result.h"

namespace Vam {

class StringUtils
{
public:
    VQ_MAKE_STATIC( StringUtils );

private:
    static std::vector< std::string > split( const std::string &orig,
                                             const std::string &delim,
                                             const int numSplits );


};

}
