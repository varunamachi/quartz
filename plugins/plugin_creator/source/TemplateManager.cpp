
#include <QHash>

#include "TemplateManager.h"
#include "Template.h"
#include "AbstractTemplateProvider.h"


namespace Quartz { namespace Plugin { namespace Creator {

const QString TemplateManager::ADAPTER_NAME{ "Template Adapter" };

struct TemplateManager::Data {
    explicit Data() {

    }

    QHash< QString, std::shared_ptr< Template >> m_templates;

    QHash< QString, QString > m_variables;
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

void TemplateManager::addVariable( const QString& key, const QString& value )
{
    m_data->m_variables.insert( key, value );
}

QString TemplateManager::variable(const QString& key)
{
    return m_data->m_variables.value( key );
}

QModelIndex TemplateManager::index( int /*row*/,
                                    int /*column*/,
                                    const QModelIndex& /*parent*/ ) const
{
    return QModelIndex{};
}

QModelIndex TemplateManager::parent( const QModelIndex& /*child*/ ) const
{
    return QModelIndex{};
}

int TemplateManager::rowCount( const QModelIndex& /*parent*/ ) const
{
    return 0;
}

int TemplateManager::columnCount( const QModelIndex& /*parent*/ ) const
{
    return 0;
}

QVariant TemplateManager::data( const QModelIndex& /*index*/,
                                int /*role*/ ) const
{
    return QVariant{};
}

bool TemplateManager::hasChildren( const QModelIndex& /*parent*/ ) const
{
    return  false;
}

} } }
