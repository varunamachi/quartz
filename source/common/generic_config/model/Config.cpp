#include <QVector>

#include "Config.h"
#include "Param.h"


namespace Quartz {

struct Config::Data
{
    Data( const QString &id,
          const QString &name )
        : m_id{ id }
        , m_name{ name }
    {

    }
    QString m_id;

    QString m_name;

    QVector< std::shared_ptr< Param >> m_params;
};

Config::Config( const QString &id, const QString &name )
    : m_data{ new Data{ id, name }}
{

}

Config::~Config()
{

}

const QString & Config::id() const
{
    return m_data->m_id;
}

const QString & Config::name() const
{
    return m_data->m_name;
}

int Config::numParams() const
{
    return m_data->m_params.size();
}

const Param * Config::paramAt( int index ) const
{
    if( index < m_data->m_params.size() ) {
        return m_data->m_params.at( index ).get();
    }
    return nullptr;
}

void Config::addParameter( std::shared_ptr< Param > param )
{
    m_data->m_params.push_back( param );
}

}
