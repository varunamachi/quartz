#pragma once

#include <vector>
#include <unordered_set>

#include "../../common/Macros.h"
#include "../../common/Result.h"
#include "../../common/Types.h"

#include "File.h"
#include "Path.h"

namespace Vq {


class FSUtils
{
public:
    enum class ConflictStrategy
    {
        Stop,
        Skip,
        Overwrite,
        Merge
    };


    VQ_MAKE_STATIC( FSUtils );

    using FilterFunction = std::function< bool( const File & )>;
    using FileList = std::vector< Vq::File >;
    using BoolResultFunc = std::function< void( Result< bool > )>;
    using DirCopyProgFunc = std::function< bool( std::size_t,
                                                  std::size_t,
                                                  const File &,
                                                  const File & )>;
    using DirProgFunc = std::function< bool( std::size_t,
                                             std::size_t,
                                             const File & )>;



    static Result< File > fileAt( const std::string &path );

    static Result< File > fileAt( const Path &path );

    static Result< bool > createRegularFile( const File &file );

    static Result< bool > deleteFile( const File &file );

    static Result< FileList > listFiles(
            const File &dir,
            FilterFunction filter = nullptr,
            std::function< void( Result< FileList >)> resultCallback = nullptr);

    static Result< bool > copyFile( const std::string &srcPath,
                                    const std::string &dstPath,
                                    const bool forceCopy = false,
                                    BoolResultFunc resultCallback = nullptr,
                                    ProgressFunction progCallback = nullptr );

    static Result< bool > moveFile( const std::string &srcPath,
                                    const std::string &dstPath,
                                    bool forceMove = false,
                                    BoolResultFunc resultCallback = nullptr,
                                    ProgressFunction progCallback = nullptr );

    static Result< bool > copyDirectory(
            const std::string &srcPath,
            const std::string &dstPath,
            ConflictStrategy conflictStrategy,
            BoolResultFunc resultCallback = nullptr,
            DirCopyProgFunc progCallback  = nullptr );

    static Result< bool > moveDirectory(
            const std::string &srcPath,
            const std::string &dstPath,
            ConflictStrategy conflictStrategy,
            BoolResultFunc resultCallback = nullptr,
            DirCopyProgFunc progCallback = nullptr );

    static Result< bool > createDirecties( const std::string &path );

    static Result< bool > createSoftLink( const std::string &targetPath,
                                          const std::string &linkPath );

    static Result< bool > deleteDir( const std::string &path,
                                     const bool force );

private:
    static Result< bool > copyFileImpl( const File &src,
                                        const File &dst,
                                        ProgressFunction progCallback );

    static Result< bool > copyDirImpl(
            const File &srcDir,
            const File &dstDir,
            bool deleteSource,
            ConflictStrategy onConflict,
            DirCopyProgFunc progCallback,
            VQ_OUT std::unordered_set< std::string > &skipped );


};

}
