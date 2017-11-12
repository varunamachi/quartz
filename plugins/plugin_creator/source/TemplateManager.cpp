
#include <QDir>
#include <QHash>

#include <common/templating/Template.h>
#include <common/templating/TemplateUtils.h>

#include "TemplateManager.h"
#include "AbstractTemplateProvider.h"


namespace Quartz { namespace Plugin { namespace Creator {

const QString TemplateManager::ADAPTER_NAME{ "Template Adapter" };

struct TemplateManager::Data {

    explicit Data() { }

    QHash< QString, std::shared_ptr< Template >> m_templates;

    QHash< QString, QString > m_variables;

    QList< Template *> m_templateList;
};

TemplateManager::TemplateManager()
    : m_data{ new Data{} }
{

}

TemplateManager::~TemplateManager()
{

}

void TemplateManager::addTemplate( std::shared_ptr< Template > tmplt )
{
    m_data->m_templates.insert( tmplt->name(), tmplt );
    m_data->m_templateList.push_back( tmplt.get() );
}

QList< Template *> TemplateManager::templates() const
{
    QList< Template *> templates;
    foreach( auto &ptr, m_data->m_templates.values() ) {
        templates.push_back( ptr.get() );
    }
    return templates;
}

const QString &TemplateManager::pluginType() const
{
    return AbstractTemplateProvider::PLUGIN_TYPE;
}

const QString &TemplateManager::pluginAdapterName() const
{
    return ADAPTER_NAME;
}

bool TemplateManager::handlePlugin( AbstractPlugin *plugin )
{
    auto tmpProvider = dynamic_cast< AbstractTemplateProvider *>( plugin );
    if( tmpProvider != nullptr ) {
        auto templates = tmpProvider->templates();
        foreach( auto &tmpl, templates ) {
            addTemplate( tmpl );
        }
    }
    return true;
}

bool TemplateManager::finalizePlugins()
{
    m_data->m_templates.clear();
    return true;
}

void TemplateManager::addVariable( const QString& key, const QString& value )
{
    m_data->m_variables.insert( key, value );
}

QString TemplateManager::variable( const QString& key )
{
    return m_data->m_variables.value( key );
}

Template * TemplateManager::templateAt( int index ) const
{
    if( index < m_data->m_templateList.size() ) {
        return m_data->m_templateList.at( index );
    }
    return nullptr;
}

int TemplateManager::numTemplates() const
{
    return m_data->m_templateList.size();
}


bool TemplateManager::loadCoreTemplates()
{
    beginResetModel();
    const QDir resDir{ ":/resources" };
    auto tmps = TemplateUtils::templatesInDir( resDir );
    foreach( auto &tmpl, tmps ) {
        addTemplate( tmpl );
    }
    endResetModel();
    return true;
}

TreeNode * TemplateManager::rootAt( int rowIndex ) const
{
    if( rowIndex < m_data->m_templateList.size() ) {
        return m_data->m_templateList.at( rowIndex );
    }
    return nullptr;
}

int TemplateManager::rootCount() const
{
    return m_data->m_templateList.size();
}

} } }
