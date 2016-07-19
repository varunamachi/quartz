
#include <memory>

#include "../Path.h"

namespace Vq {

const std::string Path::SEPERATOR( "/" );

class Path::Impl
{
public:
    explicit Impl( std::string &strPath )
        : m_strPath( strPath )
        , m_components()
    {

    }

    Impl( Impl &&other )
        : m_strPath( std::move( other.m_strPath ))
        , m_components( std::move( other.m_components ))
    {
        other.m_strPath.clear();
        other.m_components.clear();
    }

    Impl( const Impl &other )
        : m_strPath( other.m_strPath )
        , m_components( other.m_components )
    {

    }

    Impl & operator = ( const Impl & other )
    {
        m_strPath = other.m_strPath;
        m_components = other.m_components;
        return *this;
    }

    Impl & operator = ( Impl &&other )
    {
        m_strPath = std::move( other.m_strPath );
        m_components = std::move( other.m_components );
        return *this;
    }

    bool isValid() const
    {
        return ! ( m_strPath.empty() || m_components.empty() );
    }

    const std::string & strPath() const
    {
        return m_strPath;
    }

    const std::vector< std::string > & components() const
    {
        return m_components;
    }

    bool parse();

private:
    std::string m_strPath;

    std::vector< std::string > m_components;
};



Path::Path( const std::string &path )
    : m_impl( std::make_unique< Path::Impl >( path ))
{
    m_impl->parse();
}


Path::Path( const Path &other )
    : m_impl( std::make_unique< Path::Impl >( *other.m_impl ))
{

}


Path::Path( Path &&other )
    : m_impl( std::make_unique< Path::Impl >( std::move( *other.m_impl )))
{

}


Path::~Path()
{

}


Path & Path::operator = ( const Path &other )
{
    ( * this->m_impl ) = ( *other.m_impl );
    return *this;
}


Path & Path::operator = ( Path &&other )
{
    ( *this->m_impl ) = ( *other.m_impl );
    return *this;
}


bool Path::operator == ( const Path &other ) const
{
    bool result = this->m_impl->strPath() == other.m_impl->strPath();
    return result;
}


bool Path::operator ==( const std::string &strPath ) const
{
    bool result = this->m_impl->strPath() == strPath;
    return result;
}


std::string Path::toString() const
{
    return m_impl->strPath();
}


std::string Path::fileName() const
{
    std::string name{ "" };
    if( m_impl->isValid() ) {
        auto it = m_impl->components().end();
        name = * ( --it );
    }
    return name;
}


std::string Path::extension() const
{
    return "";
}

std::string Path::baseName() const
{
    return "";
}

const std::vector< std::string > & Path::components() const
{
    return m_impl->components();
}


void Path::append( const std::string &relative )
{
//    m_impl->components().emplace_back( relative );
}

Path Path::parent() const
{
    return Path{ "" };
}


}
