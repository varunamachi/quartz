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
