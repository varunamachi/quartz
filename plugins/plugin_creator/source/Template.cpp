
#include <QStringList>
#include <QMap>
#include <QVector>

#include "Template.h"

namespace Quartz { namespace Plugin { namespace Creator {

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

    QVector< Variable > m_vars;
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
    m_data->m_vars.push_back( Variable{ key, value , description });
}

const Template::Variable & Template::variable( const QString &key ) const
{
    for( auto i = 0; i < m_data->m_vars.size(); ++ i ) {
        auto &var = m_data->m_vars.at( i );
        if( var.m_name == key ) {
            return var;
        }
    }
    return EMPTY_VARIABLE;
}

const Template::Variable&Template::variableAt(int index) const
{
    if( index < m_data->m_vars.size() ) {
        return m_data->m_vars.at( index );
    }
    return EMPTY_VARIABLE;
}

const QString &Template::content() const
{
    return m_data->m_content;
}


} } }
