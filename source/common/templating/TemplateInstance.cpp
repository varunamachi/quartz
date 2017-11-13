#include <QString>
#include <QVariant>

#include "Template.h"
#include "TemplateInstance.h"

namespace Quartz {

struct TemplateInstance::Data
{
    Data( const QString &name,
          Template *parent )
     : m_name{ name }
     , m_parent{ parent }
     , m_selected{ false }
    {

    }

    QString m_name;

    Template *m_parent;

    QHash< QString, QVariant > m_paramValues;

    std::shared_ptr< GlobalConfig > m_globalConfig;

    bool m_selected;
};

TemplateInstance::TemplateInstance( const QString &name,
                                    Template *parent  )
    : TreeNode{ 1, parent }
    , m_data{ new Data{ name, parent }}
{

}

TemplateInstance::~TemplateInstance()
{

}

const QString & TemplateInstance::name() const
{
    return m_data->m_name;
}

Template * TemplateInstance::instanceOf() const
{
    return m_data->m_parent;
}

void TemplateInstance::setParamValue( const QString &paramName,
                                      const QVariant &paramValue )
{
    m_data->m_paramValues[ paramName ] = paramValue;
}

void TemplateInstance::setGlobalConfig( std::shared_ptr<GlobalConfig> gconf )
{
    m_data->m_globalConfig = gconf;
}

QVariant TemplateInstance::globalConfig( const QString &key ) const
{
    return m_data->m_globalConfig->value( key );
}

QVariant TemplateInstance::paramValue( const QString &paramName ) const
{
    return m_data->m_paramValues[ paramName ];
}

QVariant TemplateInstance::paramValue( const QString &paramName,
                                       const QString &defValue ) const
{
    if( m_data->m_paramValues.contains( paramName )) {
        return m_data->m_paramValues.value( paramName, defValue );
    }
    return m_data->m_globalConfig->value( paramName );
}

QVariant TemplateInstance::data( int column ) const
{
    switch( column ) {
    case 0: return m_data->m_name;
    }
    return "";
}

bool TemplateInstance::isEditable( int column ) const
{
    return column == 0;
}

void TemplateInstance::setData( int column, const QVariant &data )
{
    if( column == 0 ) {
        m_data->m_name= data.toString();
    }
}

}
