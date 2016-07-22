 

#include <memory>

#include "../../common/StringUtils.h"
#include "../../logger/Logging.h"
#include "../../common/Result.h"
#include "Path.h"

namespace Vq {



class Path::Data
{
public:
    Data()
        : m_components()
        , m_absolute( false )
    {

    }

    Data( const std::vector< std::string > &components,
          bool absolute )
        : m_components( components )
        , m_absolute( absolute )
    {

    }

    Data( const std::vector< std::string > &&components,
          bool absolute )
        : m_components( components )
        , m_absolute( absolute )
    {

    }

    Data( Data &&other )
        : m_components( std::move( other.m_components ))
        , m_absolute( other.m_absolute )
    {
        other.m_components.clear();
    }

    Data( const Data &other )
        : m_components( other.m_components )
        , m_absolute( other.m_absolute )
    {

    }

    Data & operator = ( const Data & other )
    {
        m_components = other.m_components;
        m_absolute = other.m_absolute;
        return *this;
    }

    Data & operator = ( Data &&other )
    {
        m_components = std::move( other.m_components );
        m_absolute = other.m_absolute;
        other.m_components.clear();
        return *this;
    }

    const std::vector< std::string > & components() const
    {
        return m_components;
    }

    std::vector< std::string > & components()
    {
        return m_components;
    }

private:
    std::vector< std::string > m_components;

    bool m_absolute;
};


Path::Path()
    : m_data( std::make_unique< Data >() )
{

}


Path::Path( const std::vector< std::string > &components, bool absolute )
    : m_data( std::make_unique< Path::Data >( components, absolute ))
{
}


Path::Path( const std::vector< std::string > &&components, bool absolute )
    : m_data( std::make_unique< Path::Data >( components, absolute ))
{
}


Path::Path( const Path &other )
    : m_data( std::make_unique< Path::Data >( *other.m_data ))
{

}


Path::Path( Path &&other )
    : m_data( std::make_unique< Path::Data >( std::move( *other.m_data )))
{

}


Path::~Path()
{

}


Path & Path::operator = ( const Path &other )
{
    ( * this->m_data ) = ( *other.m_data );
    return *this;
}


Path & Path::operator = ( Path &&other )
{
    ( *this->m_data ) = ( *other.m_data );
    return *this;
}


bool Path::operator == ( const Path &other ) const
{
    bool result = this->m_data->components() == other.m_data->components();
    return result;
}


bool Path::operator ==( const std::string &strPath ) const
{
    bool result = ( toString() == strPath );
    return result;
}

bool Path::operator != ( const Path &other ) const
{
    return ! ( ( *this ) == other );
}


bool Path::operator != ( const std::string strPath ) const
{
    return ! ( ( *this ) == strPath );
}


std::string Path::fileName() const
{
    std::string name{ "" };
    if( isValid() ) {
        auto it = m_data->components().end();
        name = * ( --it );
    }
    return name;
}


std::string Path::extension() const
{
    auto name = fileName();
    auto pos = name.find_last_of( "." );
    if( pos != std::string::npos ) {
        auto ext = name.substr( pos, name.size() - pos );
        return ext;
    }
    return "";
}

std::string Path::baseName() const
{
    auto name = fileName();
    auto pos = name.find_last_of( "." );
    if( pos != std::string::npos ) {
        auto baseName = name.substr( 0, pos );
        return baseName;
    }
    return name;
}

const std::vector< std::string > & Path::components() const
{
    return m_data->components();
}


const std::vector<std::string> &Path::components()
{
    return m_data->components();
}


Path & Path::append( const std::string &relative )
{
    if( relative.empty() ) {
        return *this;
    }
    auto result = parse( relative );
    if( result ) {
        for( const auto &cmp : result.data() ) {
            m_data->components().emplace_back( std::move( cmp ));
        }
    }
    else {
        VQ_ERROR( "Vq:Core:FS" ) << "Failed to append path " << relative
                                 << ", could not parse the given path";
    }
    return *this;
}


Path Path::parent() const
{
    std::vector< std::string > pcomps;
    auto &comps = m_data->components();
    if( comps.size() > 2 ) {
        std::copy( m_data->components().begin(),
                   m_data->components().end() - 2,
                   pcomps.begin() );

    }
    return Path{ pcomps, isAbsolute() };
}


}
