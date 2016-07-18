
#include "../Path.h"

namespace Vq {

const std::string Path::SEPERATOR( "/" );

class Path::Impl
{
public:
    explicit Impl( std::string &strPath )
        : m_strPath( strPath )
        , m_components()
        , m_baseName()
        , m_extensions()
    {

    }

    const std::string & strPath() const
    {
        return m_strPath;
    }

    const std::vector< std::string > & components() const
    {
        return m_components;
    }

    const std::string & baseName() const
    {
        return m_baseName;
    }

    const std::vector< std::string > & extensions() const
    {
        return m_extensions;
    }

private:
    std::string m_strPath;

    std::vector< std::string > m_components;

    std::string m_baseName;

    std::vector< std::string > m_extensions;

};



Path::Path( const std::string &path )
    : m_impl( std::make_unique< Path::Impl >( path ))
{

}


//Path::Path( const std::vector< std::string > &components )
//{

//}


Path::Path( const Path &other )
{

}


Path::Path( Path &&other )
{

}


Path::~Path() { }


Path & Path::operator = ( const Path &other )
{

}


Path & Path::operator = ( Path &&other )
{

}


bool Path::operator == ( Path &other )
{

}


std::string Path::toString() const
{

}


const std::string & Path::fileName() const
{

}


const std::string & Path::extension() const
{

}

const std::string & Path::baseName() const
{

}

std::vector< std::string > Path::components()
{

}


void Path::append( const std::string &relative )
{

}

Path Path::parent() const
{

}


}
