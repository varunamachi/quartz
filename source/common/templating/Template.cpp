
#include <QStringList>
#include <QMap>
#include <QVector>
#include <QVariant>

#include "../generic_config/model/Config.h"
#include "Template.h"
#include "TemplateInstance.h"

namespace Quartz {

struct Template::Data
{
    Data( const QString &name,
          const QString &content )
        : m_name{ name }
        , m_content{ content }
        , m_selected( false )
    {

    }

    QString m_name;

    QString m_content;

    bool m_selected;

    std::unique_ptr< Config > m_config;

//    QVector< std::shared_ptr< TemplateInstance >> m_instances;
};



Template::Template( const QString &name,
                    const QString &content )
    : TreeNode{ 3, nullptr }
    , m_data{ new Data{ name, content }}
{

}

Template::~Template()
{

}

QString Template::name() const
{
    return m_data->m_name;
}

void Template::setConfig( std::unique_ptr<Config> config )
{
    m_data->m_config = std::move( config );
}

Config * Template::config() const
{
    return  m_data->m_config.get();
}

const QString & Template::content() const
{
    return m_data->m_content;
}


QVariant Template::data( int column ) const
{
    switch( column ) {
    case 0: return m_data->m_selected;
    case 1: return m_data->m_name;
    case 2: return numChildren();
    }
    return QVariant{};
}

}
