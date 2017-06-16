
#include <QStringList>
#include <QMap>
#include <QHash>

#include "Template.h"

namespace Quartz {

const Template::Variable Template::EMPTY_VARIABLE{ "", "", "" };

struct Template::Data
{
    Data( const QString &name,
          const QString &content )
        : m_name{ name }
        , m_content{ content }
    {

    }

    QString m_name;

    QString m_content;

    QHash< QString, Variable > m_vars;
};



Template::Template( const QString &name,
                    const QString &content )
    : m_data{ new Data{ name, content }}
{

}

Template::~Template()
{

}

QString Template::name() const
{
    return m_data->m_name;
}

void Template::addVariable( const QString &key,
                            const QString &value,
                            const QString &description )
{
    m_data->m_vars.insert( key, Variable{ key, value , description });
}

const Template::Variable Template::variable(const QString &key) const
{
   return  m_data->m_vars.value( key, EMPTY_VARIABLE );
}

const QString &Template::content() const
{
    return m_data->m_content;
}


}
