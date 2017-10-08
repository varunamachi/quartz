
#include <QVector>

#include <common/templating/TemplateInstance.h>

#include "GenInfo.h"

namespace Quartz { namespace Plugin { namespace Creator {

struct GenInfo::Data
{
    Data( const QString &id,
          const QString &name,
          const QString &display,
          const QString &nmspace )
        : m_id{ id }
        , m_name{ name }
        , m_display{ display }
        , m_namespace{ nmspace }
    {

    }

    QVector< std::shared_ptr< TemplateInstance >> m_tmpInstances;

    QString m_id;

    QString m_name;

    QString m_display;

    QString m_namespace;

};

GenInfo::GenInfo( const QString &id,
                  const QString &name,
                  const QString &display,
                  const QString &nmspace )
    : m_data{ new Data{ id,
                        name,
                        display,
                        nmspace }}
{

}

GenInfo::~GenInfo()
{

}

const QString & GenInfo::id() const
{
    return m_data->m_id;
}

const QString & GenInfo::name() const
{
    return m_data->m_name;
}

const QString &GenInfo::display() const
{
    return m_data->m_name;
}

const QString & GenInfo::ns() const
{
    return m_data->m_namespace;
}


int GenInfo::numTemplateInstances() const
{
    return m_data->m_tmpInstances.size();
}

const TemplateInstance * GenInfo::templateInstanceAt( int i ) const
{
    TemplateInstance *instance = nullptr;
    if( i < m_data->m_tmpInstances.size() ) {
        instance = m_data->m_tmpInstances.at( i ).get();
    }
    return instance;
}

void GenInfo::addTemplateInstance( std::shared_ptr<TemplateInstance> inst )
{
    m_data->m_tmpInstances.push_back( inst );
}

void GenInfo::removeTemplateInstance( const QString &instanceName )
{
    auto index = -1;
    for( int i = 0; i < instanceName.size(); ++ i ) {
        if( m_data->m_tmpInstances.at( i )->name() == instanceName ) {
            index = i;
            break;
        }
    }
    if( index >= 0 && index < m_data->m_tmpInstances.size() ){
        m_data->m_tmpInstances.remove( index );
    }
}

} } }
