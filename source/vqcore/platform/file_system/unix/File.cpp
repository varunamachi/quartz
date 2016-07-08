
#include <string>

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
    auto code = lstat( m_data->path().c_str(), &fileStat );
    if( code != 0 ) {
        auto result = R::stream( File::Type::Unknown, errno )
                << "Failed to retrieve type of file at " << m_data->path()
                << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << result;
        return result;
    }
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
    return R::success< File::Type >( type );
}


const Path & File::path() const
{
    return m_data->pathObject();
}


Result< bool > File::exists() const
{
    auto result = R::success( true );
    auto code = access( m_data->path().c_str(), F_OK );
    if( code != 0 ) {
        result = R::stream( false, errno )
                << "File at " << m_data->path() << " does not exist"
                << R::fail;
    }
    return result;
}


Result< bool > File::isValid() const
{
    return exists();
}


Result< bool > File::isWritable() const
{
    auto result = R::success( true );
    if( access( m_data->path().c_str(), F_OK ) == 0 ) {
        auto errorCode = errno;
        if( errorCode == EACCES ) {
            result = R::success( false );
        }
        else {
            result = R::stream( false, errorCode )
                    << "Could not retrieve the access infromation for file at "
                    << m_data->path() << R::fail;
            VQ_ERROR( "Vq:Core:FS" ) << result;
        }
    }
    return result;
}


Result< bool > File::isReadable() const
{
    auto result = R::success( true );
    if( access( m_data->path().c_str(), R_OK ) == 0 ) {
        auto errorCode = errno;
        if( errorCode == EACCES ) {
            result = R::success( false );
        }
        else {
            result = R::stream( false, errorCode )
                    << "Could not retrieve the access infromation for file at "
                    << m_data->path() << R::fail;
            VQ_ERROR( "Vq:Core:FS" ) << result;
        }
    }
    return result;
}


Result< bool > File::isExecuteble() const
{
    auto result = R::failure( false, "File is not executable" );
    auto code = access( m_data->path().c_str(), X_OK );
    if( code == 0 ) {
        result = R::success( true );
    }
    return result;
}


Result< std::uint64_t > File::fileSize() const
{
    Stat fileStat;
    auto code = lstat( m_data->path().c_str(), &fileStat );
    if( code != 0 ) {
        auto result = R::stream( std::uint64_t( 0 ), errno )
                << "Failed to get size information for file at "
                << m_data->path() << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << result;
        return result;
    }
    auto size = fileStat.st_size;
    return R::success( static_cast< std::uint64_t >( size ));
}


Result< DateTime > File::creationTime() const
{
    Stat fileStat;
    auto code = lstat( m_data->path().c_str(), &fileStat );
    if( code != 0 ) {
        auto result = R::stream( DateTime{ Timestamp{ 0 }}, errno )
                << "Failed to get creation time for file at "
                << m_data->path() << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << result;
        return result;
    }
    auto timeEpoch = fileStat.st_ctime;
    return R::success( DateTime{ Timestamp{ timeEpoch }} );
}


Result<DateTime> File::lastAccessTime() const
{
    Stat fileStat;
    auto code = lstat( m_data->path().c_str(), &fileStat );
    if( code != 0 ) {
        auto result = R::stream( DateTime{ Timestamp{ 0 }}, errno )
                << "Failed to get creation time for file at "
                << m_data->path() << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << result;
        return result;
    }
    auto timeEpoch = fileStat.st_atime;
    return R::success( DateTime{ Timestamp{ timeEpoch }} );
}


Result< DateTime > File::modifiedTime() const
{
    Stat fileStat;
    auto code = lstat( m_data->path().c_str(), &fileStat );
    if( code != 0 ) {
        auto result = R::stream( DateTime{ Timestamp{ 0 }}, errno )
                << "Failed to get modification for file at "
                << m_data->path() << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << result;
        return result;
    }
    auto timeEpoch = fileStat.st_mtime;
    return R::success( DateTime{ Timestamp{ timeEpoch }} );
}


static Result< bool > changePermission( const char *path,
                                        ::mode_t permission,
                                        bool value )
{
    auto result = R::success( true );
    Stat fileStat;
    auto code = lstat( path, &fileStat );
    if( code == 0 ) {
        auto mode = fileStat.st_mode;
        if( value ) {
            mode = mode | permission;
        }
        else {
            mode = mode & ( ~ permission );
        }
        // auto newMode = mode | permission;
        code = chmod( path, newMode );
        if( code != 0 ) {
            result = R::stream( false, errno )
                    << "Failed to change permission of file at "
                    << path << " writable" << R::fail;
            VQ_ERROR( "Vq:Core:FS" ) << result;
        }
    }
    else {
        result = R::stream( false, errno )
                << "Failed to stat file at " << path << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << result;
    }
    return result;
}


Result< bool > File::setWritable( bool value )
{
    return changePermission( m_data->path().c_str(), S_IWUSR, value );
}


Result< bool > File::setReadable( bool value )
{
    return changePermission( m_data->path().c_str(), S_IRUSR, value );
}


Result< bool > File::setExecutable( bool value )
{
    return changePermission( m_data->path().c_str(), S_IXUSR, value );
}

}
