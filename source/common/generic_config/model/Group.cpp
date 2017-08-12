#include <QString>
#include <QVector>

#include "Group.h"
#include "Param.h"

namespace Quartz {

struct Group::Data
{
    Data( const QString &id,
          const QString &name,
          const QString &description )
        : m_id{ id }
        , m_name{ name }
        , m_description{ description }
    {

    }

    QString m_id;

    QString m_name;

    QString m_description;

    QVector< std::shared_ptr< Param >> m_params;

    QVector< std::shared_ptr< Group >> m_subGroups;
};

Group::Group( const QString &id,
              const QString &name,
              const QString &description )
    : m_data{ new Data{ id, name, description }}
{

}

Group::~Group()
{

}

const QString &Group::id() const
{
    return m_data->m_id;
}

const QString &Group::name() const
{
    return m_data->m_name;
}

const QString &Group::description() const
{
    return m_data->m_description;
}

void Group::addParam( std::shared_ptr< Param > param )
{
    if( param != nullptr ) {
        m_data->m_params.append( param );
    }
}

Param * Group::paramAt( int index ) const
{
    Param *param = nullptr;
    if( index < m_data->m_params.size() ) {
        param = m_data->m_params.at( index ).get();
    }
    return param;
}

void Group::addSubGroup( std::shared_ptr< Group > subGroup )
{
    if( subGroup != nullptr ) {
        m_data->m_subGroups.append( subGroup );
    }
}

Group * Group::subGroupAt( int index )
{
    Group *group = nullptr;
    if( index < m_data->m_subGroups.size() ) {
        group = m_data->m_subGroups.at( index ).get();
    }
    return group;
}

}
