
#include "../common/Constants.h"
#include "Parameters.h"

namespace Vam {

class Parameters::Data
{
public:
    using ParamMap = std::map< std::string, std::string >;

    explicit Data( ParamMap paramMap )
        : m_paramMap( paramMap )
    {

    }

    inline ParamMap & paramMap()
    {
        return m_paramMap;
    }

private:
    ParamMap m_paramMap;
};

Parameters::Parameters( std::map< std::string, std::string > &params )
    : m_data( std::make_unique< Parameters::Data >( params ))
{
}


void Parameters::addParam( const std::string &key, const std::string &value )
{
    m_data->paramMap().insert( key, value );
}


void Parameters::removeParam( const std::string &key )
{
    m_data->paramMap().erase( key );
}


const std::string & Parameters::param( const std::string &key ) const
{
    auto it = m_data->paramMap().find( key );
    if( it != std::end( m_data->paramMap() )) {
        return it->second;
    }
    return Constants::EMPTY_STRING;
}

}
