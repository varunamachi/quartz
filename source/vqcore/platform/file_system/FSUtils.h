#pragma once

#include <vector>

#include "../../common/Macros.h"
#include "../../common/Result.h"
#include "../../common/Types.h"

#include "File.h"
#include "Path.h"

namespace Vq {

class FSUtils
{
public:
    VQ_MAKE_STATIC( FSUtils );

    using FilterFunction = std::function< bool( const File & )>;
    using FileList = std::vector< Vq::File >;
    using BoolResultFunc = std::function< void( Result< bool > )>;


    static Result< File > fileAt( const std::string &path );

    static Result< File > fileAt( const Path &path );

    static Result< bool > createRegularFile( const File &file );

    static Result< bool > deleteFile( const File &file );

    static Result< FileList > listFiles(
            const File &dir,
            FilterFunction filter,
            std::function< void( Result< FileList >)> resultCallback = nullptr);

    static Result< bool > copyFile( const std::string &srcPath,
                                    const std::string &dstPath,
                                    const bool force = false,
                                    BoolResultFunc resultCallback = nullptr,
                                    ProgressFunction progCallback = nullptr );

    static Result< bool > moveFile( const std::string &srcPath,
                                    const std::string &dstPath,
                                    BoolResultFunc resultCallback = nullptr,
                                    ProgressFunction progCallback = nullptr );

    static Result< bool > copyDirectory(
            const std::string &srcPath,
            const std::string &dstPath,
            BoolResultFunc resultCallback = nullptr,
            DetailedProgressFunc progCallback  = nullptr );

    static Result< bool > moveDirectory(
            const std::string &srcPath,
            const std::string &dstPath,
            BoolResultFunc resultCallback = nullptr,
            DetailedProgressFunc progCallback = nullptr );

    static Result< bool > createDirecties( const std::string &path );

    static Result< bool > createSoftLink( const std::string &targetPath,
                                          const std::string &linkPath );

    static Result< bool > deleteDir( const std::string &path,
                                     const bool force );

private:

};

}
