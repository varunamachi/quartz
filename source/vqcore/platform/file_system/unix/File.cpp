
#include <string>
#include <mutex>
#include <thread>

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "../../../logger/Logging.h"
#include "../File.h"
#include "../Path.h"

namespace Vq  {

using Stat = struct stat;

class File::Data
{
public:
    VQ_NO_COPY( Data );

    explicit Data( const std::string &path )
        : m_path( path )
        , m_pathObj( path )
    {
    }

    Data( Data &&other )
        : m_path( std::move( other.m_path ))
        , m_pathObj( std::move( other.m_pathObj ))
    {
        other.m_path = "";
        other.m_pathObj = Path{ "" };
    }

    inline const std::string & path() const
    {
        return m_path;
    }

    inline std::string path()
    {
        return m_path;
    }

    inline void setPath( const std::string &path )
    {
        m_path = path;
    }

    inline const Path & pathObject() const
    {
        return m_pathObj;
    }

private:
    std::string m_path;

    Path m_pathObj;

};

File::File( const Path &path )
    : m_data( std::make_unique< File::Data >( path ))
{

}


File::File( File &&other )
    : m_data( std::move( other.m_data ))
{

}


File::~File()
{

}


File & File::operator = ( File &&other )
{
    m_data = std::move( other.m_data );
}


bool File::operator == ( const File &other ) const
{
    bool result = m_data->path() == other.m_data->path();
    return result;
}


Result< File::Type > File::type() const
{
    Stat fileStat;
    auto result =  Result< File::Type >::failure(
                File::Type::Unknown,
                "Failed to retrieve file type" );
    auto code = lstat( m_data->path().c_str(), &fileStat );
    if( code == 0 ) {
        auto type = File::Type::Unknown;
        if( S_ISREG( fileStat.st_mode )) {
            type = File::Type::Regular;
        }
        else if( S_ISDIR( fileStat.st_mode )) {
            type = File::Type::Dir;
        }
        else if( S_ISCHR( fileStat.st_mode )) {
            type = File::Type::Device;
        }
        else if( S_ISBLK( fileStat.st_mode )) {
            type = File::Type::Device;
        }
        else if( S_ISLNK( fileStat.st_mode )) {
            type = File::Type::Link;
        }
        else if( S_ISFIFO( fileStat.st_mode )) {
            type = File::Type::Fifo;
        }
        else if( S_ISSOCK( fileStat.st_mode )) {
            type = File::Type::Socket;
        }
        result = Result< File::Type >::success( type );
    }
    else {
        VQ_ERROR( "Vq:Core:FS" )
                << "Failed to retrieve type of file at " << m_data->path()
                << " - ErrorCode " << errno;
    }
    return result;
}


const Path & File::path() const
{
    return m_data->pathObject();
}


Result< bool > File::exists() const
{
    auto result = Result< bool >::failure( "File does not exist" );
    auto code = access( m_data->path().c_str(), F_OK );
    if( code == 0 ) {
        result = Result< bool >::success();
    }
    return result;
}


Result< bool > File::isValid() const
{
    return exists();
}


Result< bool > File::isWritable() const
{
    auto result = Result< bool >::failure( "File is not writable" );
    if( access( m_data->path().c_str(), F_OK ) ) {
        result = Result< bool >::success();
    }
    return result;
}


Result< bool > File::isReadable() const
{
    auto result = Result< bool >::failure( "File is not readable" );
    auto code = access( m_data->path().c_str(), R_OK );
    if( code == 0 ) {
        result = Result< bool >::success();
    }
    return result;
}


Result< bool > File::isExecuteble() const
{
    auto result = Result< bool >::failure( "File is not executable" );
    auto code = access( m_data->path().c_str(), X_OK );
    if( code == 0 ) {
        result = Result< bool >::success();
    }
    return result;
}


Result< std::uint64_t > File::fileSize() const
{
    auto result = Result< std::uint64_t >::failure(
                0,
                "Failed to retrieve file size information" );
    Stat fileStat;
    auto code = lstat( m_data->path().c_str(), &fileStat );
    if( code == 0 ) {
        auto size = fileStat.st_size;
        result = Result< std::uint64_t >::success( size );
    }
    else {
        VQ_ERROR( "Vq:Core:FS" ) << "Failed to get size information for file "
                                    "at " << m_data->path() << " ErrorCode: "
                                 << errno;
    }
    return result;
}


Result< DateTime > File::creationTime() const
{
    return Result< DateTime >::failure( DateTime{ Timestamp{ 0 }},
                                        "Not implemented" );
}


Result< DateTime > File::modifiedTime() const
{
    return Result< DateTime >::failure( DateTime{ Timestamp{ 0 }},
                                        "Not implemented" );
}


Result< bool > File::makeWritable()
{
    auto result = Result< bool >::failure(
                "Could not stat file before making file writable" );
    Stat fileStat;
    auto code = lstat( m_data->path().c_str(), &fileStat );
    if( code == 0 ) {
        auto mode = fileStat.st_mode;
        auto newMode = mode | S_IWUSR;
        code = chmod( m_data->path().c_str(), newMode );
        if( code == 0 ) {
            result = Result< bool >::success();
        }
        else {
            result = Result< bool >::failure(
                            "Could not make file writable" );
            VQ_ERROR( "Vq:Core:FS" )
                    << "Failed to make file at " << m_data->path()
                    << " writable - ErrorCode: " << errno;

        }
    }
    else {
        VQ_ERROR( "Vq:Core:FS" ) << "Failed to stat file at " << m_data->path()
                                 << " - ErrorCode: " << errno;
     }
    return result;
}


Result< bool > File::makeReadable()
{
    auto result = Result< bool >::failure(
                "Could not stat file before making file readable" );
    Stat fileStat;
    auto code = lstat( m_data->path().c_str(), &fileStat );
    if( code == 0 ) {
        auto mode = fileStat.st_mode;
        auto newMode = mode | S_IRUSR;
        code = chmod( m_data->path().c_str(), newMode );
        if( code == 0 ) {
            result = Result< bool >::success();
        }
        else {
            result = Result< bool >::failure(
                            "Could not make file readable" );
            VQ_ERROR( "Vq:Core:FS" )
                    << "Failed to make file at " << m_data->path()
                    << " readable - ErrorCode: " << errno;

        }
    }
    else {
        VQ_ERROR( "Vq:Core:FS" ) << "Failed to stat file at " << m_data->path()
                                 << " - ErrorCode: " << errno;
     }
    return result;
}


Result< bool > File::makeExecutable()
{
    auto result = Result< bool >::failure(
                "Could not stat file before making file executable" );
    Stat fileStat;
    auto code = lstat( m_data->path().c_str(), &fileStat );
    if( code == 0 ) {
        auto mode = fileStat.st_mode;
        auto newMode = mode | S_IXUSR;
        code = chmod( m_data->path().c_str(), newMode );
        if( code == 0 ) {
            result = Result< bool >::success();
        }
        else {
            result = Result< bool >::failure(
                            "Could not make file executable" );
            VQ_ERROR( "Vq:Core:FS" )
                    << "Failed to make file at " << m_data->path()
                    << " executable - ErrorCode: " << errno;

        }
    }
    else {
        VQ_ERROR( "Vq:Core:FS" ) << "Failed to stat file at " << m_data->path()
                                 << " - ErrorCode: " << errno;
     }
    return result;
}

}
