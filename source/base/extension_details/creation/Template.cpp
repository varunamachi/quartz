
#include <QStringList>
#include <QMap>
#include <QHash>

#include "Template.h"

namespace Quartz {

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

    QHash< QString, QString > m_vars;
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
                                const QString &value )
{
    m_data->m_vars.insert( key, value );
}

QString Template::variable(const QString &key) const
{
    m_data->m_vars.value( key, "" );
}

const QString &Template::content() const
{
    return m_data->m_content;
}


}
