
#include <QStringList>
#include <QMap>
#include <QHash>

#include "TemplateInfo.h"

namespace Quartz {

struct TemplateInfo::Data
{
    QHash< QString, QString > m_vars;

    QMap< QString, QString > m_templates;
};



TemplateInfo::TemplateInfo()
    : m_data{ new Data{} }
{

}

TemplateInfo::~TemplateInfo()
{

}

void TemplateInfo::addVariable( const QString &key,
                                const QString &value )
{
    m_data->m_vars.insert( key, value );
}

void TemplateInfo::addTemplate( const QString &templateName,
                                const QString &content )
{
    m_data->m_templates.insert( templateName, content );
}

QStringList TemplateInfo::templateNames() const
{
    QStringList names;
    foreach( const QString &key, m_data->m_templates.values() ) {
        names << key;
    }
    return names;
}

QString TemplateInfo::templateFor( const QString &templateName ) const
{
    return m_data->m_templates.value( templateName );
}



}
