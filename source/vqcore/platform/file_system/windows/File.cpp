
#include <Windows.h>
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
        , m_pathObj( Path::create( path ).data() )
    {
    }

    Data( Data &&other )
        : m_path( std::move( other.m_path ))
        , m_pathObj( std::move( other.m_pathObj ))
    {
        other.m_path = "";
        other.m_pathObj = Path();
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

    inline HANDLE fileHandle() const
    {
        HANDLE handle = CreateFileA( m_path.c_str(),
                                     GENERIC_READ,
                                     FILE_SHARE_READ,
                                     NULL,
                                     OPEN_EXISTING,
                                     FILE_ATTRIBUTE_NORMAL,
                                     NULL );
        return handle;
    }


private:
    std::string m_path;

    Path m_pathObj;

};

File::File()
    : m_data( std::make_unique< File::Data >( "" ))
{

}


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
    return *this;
}


bool File::operator == ( const File &other ) const
{
    bool result = m_data->path() == other.m_data->path();
    return result;
}


Result< File::Type > File::type() const
{
    auto handle = m_data->fileHandle();
    if( handle == INVALID_HANDLE_VALUE ) {
        auto ecode = ::GetLastError();
        auto result = R::stream( File::Type::Unknown, ecode )
                << "Failed to open file at " << m_data->path()
                << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << result;
        return result;
    }

    auto fromAttribs = [ this ]() -> Result< File::Type >
    {
        auto attrib = ::GetFileAttributes( m_data->path().c_str() );
        if( attrib == INVALID_FILE_ATTRIBUTES ) {
            auto errorCode = VQ_TO_ERR( ::GetLastError() );
            auto result = R::stream( File::Type::Unknown, errorCode )
            << "Failed to retrieve attributes for file at "
            << m_data->path() << R::fail;
            VQ_ERROR( "Vq:Core:FS" ) << result;
            return result;
        }
        auto fileType = File::Type::Unknown;
        if(( attrib & FILE_ATTRIBUTE_DIRECTORY ) != 0 ) {
            fileType = File::Type::Dir;
        }
        else if(( attrib & FILE_ATTRIBUTE_NORMAL ) != 0 ) {
            fileType = File::Type::Regular;
        }
        else if(( attrib & FILE_ATTRIBUTE_REPARSE_POINT ) != 0 ) {
            fileType = File::Type::Link;
        }
        return R::success< File::Type >( fileType );
    };

    auto type = ::GetFileType( handle );
    auto errorCode = ::GetLastError();
    if( errorCode != NO_ERROR ) {
        auto result = R::stream( File::Type::Unknown, errorCode )
                << "Failed to retrieve type of file at " << m_data->path()
                << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << result;
        return result;
    }

    auto result = R::success< File::Type >( File::Type::Unknown );
    if( type == FILE_TYPE_CHAR ) {
        result = R::success< File::Type >( File::Type::Device );
    }
    else if( type == FILE_TYPE_PIPE ) {
        result = R::success< File::Type >( File::Type::Pipe_Or_Socket );
    }
    else if( type == FILE_TYPE_DISK ) {
        result = fromAttribs();
    }

    return result;
}


const Path & File::path() const
{
    return m_data->pathObject();
}


bool File::exists() const
{
    auto handle = m_data->fileHandle();
    auto error = GetLastError();
    auto result = ( handle == INVALID_HANDLE_VALUE
                            &&  ( error == ERROR_FILE_NOT_FOUND
                                || error == ERROR_PATH_NOT_FOUND
                                || error == ERROR_INVALID_DRIVE ));
    if( ! result && handle == INVALID_HANDLE_VALUE ) {
        VQ_ERROR( "Vq:Core:FS" )
                << "Failed to check existance of file at " << m_data->path()
                << " Error Code: " << VQ_TO_ERR( error );
    }
    return result;
}


bool File::isValid() const
{
    return exists();
}


bool File::isWritable() const
{
    auto result = true;
    auto attr = ::GetFileAttributes( m_data->path().c_str() );
    if( attr == INVALID_FILE_ATTRIBUTES ) {
        VQ_ERROR( "Vq:Core:FS" ) 
            << "Could not get file attributes for file "
            << VQ_TO_ERR( ::GetLastError() );
        result = false;
    }
    else if(( attr & FILE_ATTRIBUTE_READONLY ) != 0 ) {
        result = false;
    }
    return result;
}


bool File::isReadable() const
{
    auto result = true;
    auto attr = GetFileAttributes( m_data->path().c_str() );
    auto errorCode = GetLastError();
    if( attr == INVALID_FILE_ATTRIBUTES ) {
        if( errorCode != ERROR_ACCESS_DENIED ) {
            VQ_ERROR( "Vq:Core:FS" )
                << "Failed to read attributes of file " << m_data->path()
                << ". Error Code: " << errorCode;
        }
        result = false;
    }
    return result;
}


bool File::isExecuteble() const
{
    return true;
}


Result< std::uint64_t > File::fileSize() const
{
    DWORD upper = 0;
    auto lower = ::GetFileSize( m_data->fileHandle(), &upper  );
    if( lower != INVALID_FILE_SIZE ) {
        auto shiftVal = sizeof( DWORD ) * 8;
        auto fullSize = ( upper << shiftVal ) + lower;
        return R::success< std::uint64_t >( fullSize );
    }
    auto result = R::stream( std::uint64_t( 0 ), VQ_TO_ERR( ::GetLastError() ))
            << "Failed to get size of file at " << m_data->path()
            << R::fail;
    VQ_ERROR( "Vq:Core:FS" ) << result;
    return result;
}


Result< DateTime > File::creationTime() const
{
    FILETIME fileTime;
    auto code = ::GetFileTime( m_data->fileHandle(),
                               &fileTime,
                               nullptr,
                               nullptr );
    if( code != FALSE ) {
        auto time = ( static_cast< std::uint64_t >(
                          fileTime.dwHighDateTime ) << 32 )
                + ( fileTime.dwLowDateTime & 0xFFFFFFFF);
        return R::success( DateTime{ Timestamp{ time }});
    }
    auto result = R::stream( DateTime{ Timestamp{ 0 }},
                             VQ_TO_ERR( ::GetLastError() ))
            << "Failed to retrieve the creation time of file at "
            << m_data->path() << R::fail;
    VQ_ERROR( "Vq:Core:FS" ) << result;
    return result;
}


Result<DateTime> File::lastAccessTime() const
{
    FILETIME fileTime;
    auto code = ::GetFileTime( m_data->fileHandle(),
                               nullptr,
                               &fileTime,
                               nullptr );
    if( code != FALSE ) {
        auto time = ( static_cast< std::uint64_t >(
                          fileTime.dwHighDateTime ) << 32 )
                + ( fileTime.dwLowDateTime & 0xFFFFFFFF);
        return R::success( DateTime{ Timestamp{ time }});
    }
    auto result = R::stream( DateTime{ Timestamp{ 0 }},
                             VQ_TO_ERR( ::GetLastError() ))
            << "Failed to retrieve the last access time of file at "
            << m_data->path() << R::fail;
    VQ_ERROR( "Vq:Core:FS" ) << result;
    return result;
}


Result< DateTime > File::modifiedTime() const
{
    FILETIME fileTime;
    auto code = ::GetFileTime( m_data->fileHandle(),
                               nullptr,
                               nullptr,
                               &fileTime );
    if( code != FALSE ) {
        auto time = ( static_cast< std::uint64_t >(
                          fileTime.dwHighDateTime ) << 32 )
                + ( fileTime.dwLowDateTime & 0xFFFFFFFF);
        return R::success( DateTime{ Timestamp{ time }});
    }
    auto result = R::stream( DateTime{ Timestamp{ 0 }},
                             VQ_TO_ERR( ::GetLastError() ))
            << "Failed to retrieve the last mpodification time of file at "
            << m_data->path() << R::fail;
    VQ_ERROR( "Vq:Core:FS" ) << result;
    return result;
}


Result< bool > File::setWritable( bool value )
{
    auto attr = ::GetFileAttributes( m_data->path().c_str() );
    if( attr == INVALID_FILE_ATTRIBUTES ) {
        auto result = R::stream( false, VQ_TO_ERR( ::GetLastError() ))
                << "Failed to get attributes of the file at " << m_data->path()
                << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << result;
        return result;
    }
    auto result = R::success( true );
    if( value ) {
        attr = attr & static_cast< unsigned long >( ~ FILE_ATTRIBUTE_READONLY );
    }
    else {
        attr = attr | FILE_ATTRIBUTE_READONLY;
    }
    auto code = ::SetFileAttributesA( m_data->path().c_str(), attr );
    if( code == 0 ) {
        result = R::stream( false, VQ_TO_ERR( ::GetLastError() ))
                << "Failed to set attributes of the file at " << m_data->path()
                << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << result;
    }
    return result;
}


Result< bool > File::setReadable( bool value )
{
    struct _stat stat;
    auto code = _stat( m_data->path().c_str(), &stat );
    if( code != 0 ) {
        auto result = R::stream( false, errno )
                << "Failed to stat file at " << m_data->path()
                << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << result;
        return result;
    }
    auto result = R::success( true );
    auto mode = stat.st_mode;
    if( value ) {
        mode = ( mode | _S_IREAD );
    }
    else {
        mode = ( mode & (~ _S_IREAD ));
    }
    code = _chmod( m_data->path().c_str(), mode );
    if( code != 0 ) {
        result = R::stream( false, errno )
                << "Failed to change the read permission for file at "
                << m_data->path() << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << result;
    }
    return result;
}


Result< bool > File::setExecutable( bool /*value*/ )
{
    auto result = R::stream( true ) << "This operation is not supported on "
                                       "Windows platform" << R::succeed;
    VQ_WARN( "Vq:Core:FS" ) << result;

    return result;
}

}
