#pragma once

#include <vector>

#include "../../common/Macros.h"
#include "../../common/Result.h"

#include "File.h"
#include "Path.h"

namespace Vam {

class FSUtils
{
public:
    VQ_MAKE_STATIC( FSUtils );

    static Result< File > fileAt( const std::string &path );

    static Result< File > fileAt( const Path &path );

    static Result< bool > createRegularFile( const File &file );

    static Result< bool > deleteFile( const File &file );

    static Result< std::vector< File >> listFiles( const File &file );

    static Result< Path > mergePath( const Path &one, const Path &two );

private:
};

}
