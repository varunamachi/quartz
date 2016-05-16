
#include "Parameters.h"

namespace Vam {

Parameters::Parameters( QHash< std::string, QVariant > &params )
    : m_params( params )
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
