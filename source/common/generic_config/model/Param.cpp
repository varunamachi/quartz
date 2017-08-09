#include <QString>
#include <QVector>

#include "Param.h"

namespace Quartz {

struct Param::Data
{
    Data( const QString &id,
          const QString &name,
          const QString &category )
        : m_id( id )
        , m_name( name )
        , m_category( category )
    {
    }

    QString m_id;

    QString m_name;

    QString m_category;

    QVector< std::shared_ptr< Param >> m_subParams;

};

Param::Param( const QString &id,
              const QString &name,
              const QString &category )
    : m_data{ new Data{ id, name, category  }}
{

}

Param::~Param()
{

}

const QString & Param::id() const
{
    return m_data->m_id;
}

const QString & Param::name() const
{
    return m_data->m_name;
}

const QString & Param::category() const
{
    return m_data->m_category;
}

void Param::addSubParam( std::shared_ptr< Param > param )
{
    m_data->m_subParams.append( param );
}


int Param::numSubParams() const
{
    return m_data->m_subParams.size();
}

Param * Param::subParam( int index ) const
{
    Param *param = nullptr;
    if( index < m_data->m_subParams.size() ) {
        param = m_data->m_subParams.at( index ).get();
    }
    return nullptr;
}

}
