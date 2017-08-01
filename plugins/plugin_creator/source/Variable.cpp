#include <QString>
#include <QVariant>

#include "Variable.h"

namespace Quartz { namespace Plugin { namespace Creator {

struct Variable::Data
{
    Data( const QString &name,
          const QString &description,
          const QString &defaultValue )
        : m_name( name )
        , m_description( description )
        , m_defaultValue( defaultValue )
    {

    }

    Data( const Data &other )
        : m_name{ other.m_name }
        , m_description{ other.m_description }
        , m_defaultValue{ other.m_defaultValue }
    {

    }

    QString m_name;

    QString m_description;

    QString m_defaultValue;

};

Variable::Variable( const QString &name,
                    const QString &description,
                    const QString &defaultValue )
    : m_data{ new Data{ name, description, defaultValue }}
{

}

Variable::Variable( const Variable &other )
    : m_data{ new Data { other.m_data->m_name,
              other.m_data->m_description,
              other.m_data->m_defaultValue }}
{
}

Variable &Variable::operator =( const Variable &other )
{
    m_data->m_name = other.m_data->m_name;
    m_data->m_description = other.m_data->m_description;
    m_data->m_defaultValue = other.m_data->m_defaultValue;
    return *this;
}

Variable::~Variable()
{

}

const QString & Variable::name() const
{
    return m_data->m_name;
}

const QString & Variable::defaultValue() const
{
    return m_data->m_defaultValue;
}

const QString & Variable::description() const
{
    return m_data->m_description;
}

} } }
