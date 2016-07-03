
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
    auto errNum = lstat( m_data->path().c_str(), &fileStat );
    if( errNum == 0 ) {
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
                << " - ErrorCode " << errNum;
    }
    return result;

}


const Path & File::path() const
{
    return m_data->pathObject();
}


Result< bool > File::exists() const
{
}


Result< bool > File::isValid() const
{

}


Result< bool > File::isWritable() const
{

}


Result< bool > File::isReadable() const
{

}


Result< bool > File::isExecuteble() const
{

}


Result< std::uint64_t > File::fileSize() const
{

}


Result< DateTime > File::creationTime() const
{

}


Result< DateTime > File::modifiedTime() const
{

}


Result< bool > File::makeWritable()
{

}


Result< bool > File::makeReadable()
{

}


Result< bool > File::makeExecutable()
{

}

}
