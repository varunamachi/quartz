#include <QString>
#include <QVector>

#include "Param.h"

namespace Quartz {

struct Param::Data
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

};

Param::Param( const QString &id,
              const QString &name,
              const QString &description )
    : m_data{ new Data{ id, name, description  }}
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

const QString &Param::description() const
{
    return m_data->m_description;
}

}
