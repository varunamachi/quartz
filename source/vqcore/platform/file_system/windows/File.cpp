
#include <Windows.h>

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


Result< bool > File::exists() const
{
    auto result = R::success( true );
    auto handle = m_data->fileHandle();
    auto error = GetLastError();
    auto doesNotExist = ( handle == INVALID_HANDLE_VALUE
                          &&  ( error == ERROR_FILE_NOT_FOUND
                                || error == ERROR_PATH_NOT_FOUND
                                || error == ERROR_INVALID_DRIVE ));
    if( doesNotExist ) {
        result = R::success( false );
    }
    else if( handle == INVALID_HANDLE_VALUE ) {
        result = R::stream( false, VQ_TO_ERR( error ))
                << "Failed to check existance of file at " << m_data->path()
                << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << result;
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
    auto attr = ::GetFileAttributes( m_data->path().c_str() );
    if(( attr & FILE_ATTRIBUTE_READONLY ) != 0 ) {
        result = R::success( false );
    }
    else if( attr == INVALID_FILE_ATTRIBUTES ) {
        result = R::stream( false, VQ_TO_ERR( ::GetLastError() ))
                << "Could not get file attributes for file "
                << m_data->path() << R::fail;
        VQ_ERROR( "Vq:Core:FS" ) << result;

    }
    return result;
}


Result< bool > File::isReadable() const
{
    auto result = R::success( true );
    auto attr = GetFileAttributes( m_data->path().c_str() );
    auto errorCode = GetLastError();
    if( attr == INVALID_FILE_ATTRIBUTES && errorCode == ERROR_ACCESS_DENIED ) {
        result = R::success( false );
    }
    else if( attr == INVALID_FILE_ATTRIBUTES ) {
        result = R::stream( false, errorCode )
                << "Failed to read attributes of file " << m_data->path()
                << R::fail;
        VQ_ERROR( "Vq:Core:FS" )  << result;
    }
    return result;
}


Result< bool > File::isExecuteble() const
{
    return R::success( true );
}


Result< std::uint64_t > File::fileSize() const
{
    auto result = R::success( std::uint64_t( 0 ));



    return result;
}


Result< DateTime > File::creationTime() const
{
    return R::failure( DateTime{ Timestamp{ 0 }}, "Not implemented" );
}


Result< DateTime > File::modifiedTime() const
{
    return R::failure( DateTime{ Timestamp{ 0 }}, "Not implemented" );
}


Result< bool > File::makeWritable()
{
    auto result = R::success( true );
    return result;
}


Result< bool > File::makeReadable()
{
    auto result = R::success( true );
    return result;
}


Result< bool > File::makeExecutable()
{
    auto result = R::success( true );
    return result;
}

}
