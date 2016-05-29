#pragma once

#include <memory>
#include <string>

#include "../../common/Result.h"

namespace Vam {

class Path;

class File
{
public:
    enum class Type
    {
        Regular,
        Dir,
        Link,
        Device,
        Unknown
    };

    explicit File( const Path& path );

    Result< Type > type() const;

    Path & path() const;

    Result< bool >  exists() const;

    Result< bool >  isValid() const;

    Result< bool > isWritable() const;

    Result< bool >  isReadable() const;

    Result< bool >  isExecuteble() const;

    Result< bool > fileSize() const;


private:
    class Impl;
    std::unique_ptr< Impl > m_impl;
};

}

