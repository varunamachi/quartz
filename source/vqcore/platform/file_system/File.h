#pragma once

#include <memory>
#include <string>
#include <ostream>

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
        Fifo,
        Socket,
        Pipe_Or_Socket,
        Unknown
    };

    VQ_NO_COPY( File );

    File();

    explicit File( const std::string &path );

    explicit File( const Path &path );

    File( File &&other );

    ~File();

    File & operator = ( File &&other );

    bool operator == ( const File &other ) const;

    Result< Type > type() const;

    const Path & path() const;

    bool exists() const;

    bool isValid() const;

    bool isWritable() const;

    bool isReadable() const;

    bool isExecuteble() const;

    Result< std::uint64_t > fileSize() const;

    Result< DateTime > creationTime() const;

    Result< DateTime > lastAccessTime() const;

    Result< DateTime > modifiedTime() const;

    Result< bool > setWritable( bool value );

    Result< bool > setReadable( bool value );

    Result< bool > setExecutable( bool value );

    friend std::ostream & operator<<( std::ostream &stream, const File &file );

private:
    class Data;
    std::unique_ptr< Data > m_data;
};

}

