
#include "Parameters.h"

namespace Vam {

Parameters::Parameters( QHash< QString, QVariant > &params )
    : m_params( params )
{
}


void Parameters::addParam( const QString &key, const QVariant &value )
{
    m_params.insert( key, value );
}


void Parameters::removeParam( const QString &key )
{
    m_params.remove( key );
}


const QVariant Parameters::param( const QString &key ) const
{
    return m_params.value( key );
}

}
