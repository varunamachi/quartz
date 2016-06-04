#pragma once

#include <memory>
#include <string>

#include "../../common/Result.h"
#include "../../common/DateTime.h"
#include "../../common/Macros.h"


namespace Vq {

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

    VQ_NO_COPY( File );

    explicit File( const Path& path );

    explicit File( File &&other );

    ~File();

    File & operator = ( File &&other );

    bool operator == ( const File &other ) const;

    Result< Type > type() const;

    Path & path() const;

    Result< bool >  exists() const;

    Result< bool >  isValid() const;

    Result< bool > isWritable() const;

    Result< bool >  isReadable() const;

    Result< bool >  isExecuteble() const;

    Result< bool > fileSize() const;

    Result< DateTime > creationTime() const;

    Result< DateTime > modifiedTime() const;

    Result< bool > makeWritable();

    Result< bool > makeReadable();

    Result< bool > makeExecutable();

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;
};

}
