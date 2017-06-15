
#include <QHash>

#include "TemplateManager.h"
#include "Template.h"
#include "AbstractTemplateProvider.h"


namespace Quartz {

const QString TemplateManager::ADAPTER_NAME{ "Template Adapter" };

struct TemplateManager::Data {
    explicit Data() {

    }

    QHash< QString, std::shared_ptr< Template >> m_templates;
};

TemplateManager::TemplateManager()
{

}

TemplateManager::~TemplateManager()
{

}

void TemplateManager::addTemplate( std::shared_ptr<Template> tmplt )
{
    m_data->m_templates.insert( tmplt->name(), tmplt );
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




}
