#pragma once

#include <vector>

#include "../../common/Macros.h"
#include "../../common/Result.h"

#include "File.h"
#include "Path.h"

namespace Vq {

class FSUtils
{
public:
    VQ_MAKE_STATIC( FSUtils );

    using FilterFunction = std::function< bool( const File & )>;
    using ProgressFunction = std::function< bool( std::uint8_t progress )>;
    using FileList = std::vector< Vq::File >;

    static Result< File > fileAt( const std::string &path );

    static Result< File > fileAt( const Path &path );

    static Result< bool > createRegularFile( const File &file );

    static Result< bool > deleteFile( const File &file );

    static Result< FileList > listFiles( const File &dir,
                                         FilterFunction filter,
                                         ProgressFunction progFunc );

    static Result< bool > copyFile( const std::string &srcPath,
                                    const std::string &dstPath)


private:
};

}
