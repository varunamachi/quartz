
#include "Parameters.h"

namespace Vam {

class Parameters::Data
{
public:
    using ParamMap = std::map< std::string, std::string >;
    explicit Data( )

    inline ParamMap & paramMap()
    {
        return m_paramMap;
    }

private:
    ParamMap m_paramMap;
};

Parameters::Parameters( QHash< std::string, QVariant > &params )
    : m_data( params )
{
}


void Parameters::addParam( const std::string &key, const QVariant &value )
{
    m_params.insert( key, value );
}


void Parameters::removeParam( const std::string &key )
{
    m_params.remove( key );
}


const QVariant Parameters::param( const std::string &key ) const
{
    return m_params.value( key );
}

}
