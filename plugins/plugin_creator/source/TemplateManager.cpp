
#include <QHash>

#include "TemplateManager.h"
#include "Template.h"
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

QModelIndex TemplateManager::index( int row,
                                    int column,
                                    const QModelIndex &parent ) const
{
    QModelIndex index;
    if( ! hasIndex( row, column, parent )) {
        return index;
    }
    if( parent.isValid() ) {
        auto node = static_cast< ITreeNode * >( parent.internalPointer() );
        auto child = node->child( row );
        if( child != nullptr ) {
            index = createIndex( row, column, child );
        }
    } else {
        auto node = m_data->m_templateList.at( row );
        if( node != nullptr ) {
            index = createIndex( row, column, node );
        }
    }
    return index;
}

QModelIndex TemplateManager::parent( const QModelIndex& childIndex ) const
{
    if( ! childIndex.isValid() ) {
        return QModelIndex{};
    }
    auto index = QModelIndex{};
    auto node = static_cast< ITreeNode *>( childIndex.internalPointer() );
    if( node != nullptr && node->parent() != nullptr ) {
        auto parent = node->parent();
        auto grandParent = parent->parent();
        auto row = 0;
        if( grandParent != nullptr ) {
            row = grandParent->indexOfChild( parent );
        }
        if( row != -1 ) {
            //only zeroth column ??
            index = createIndex( row, 0, parent );
        }
    }
    return index;

}

int TemplateManager::rowCount( const QModelIndex& parent ) const
{
    //default is list of templates
    auto count = m_data->m_templateList.size();
    if( parent.isValid() ) {
        auto node = static_cast< ITreeNode *>( parent.internalPointer() );
        count = node->numChildren();
    }
    return count;
}

int TemplateManager::columnCount( const QModelIndex& parent ) const
{
    //default is list of templates
    auto count = 0;
    if( parent.isValid() ) {
        auto node = static_cast< ITreeNode *>( parent.internalPointer() );
        count = node->numFields();
    }
    return count;
}

QVariant TemplateManager::data( const QModelIndex& index,
                                int role ) const
{
    QVariant data;
    if( index.isValid() ) {
        auto node = static_cast< ITreeNode *>( index.internalPointer() );
        if( node != nullptr ) {
            data = node->data( index.column() )            ;
        }
    }
    return data;
}

bool TemplateManager::hasChildren( const QModelIndex& parent ) const
{
    auto has = ! m_data->m_templateList.isEmpty();
    if(  parent.isValid() ) {
        auto node = static_cast< ITreeNode *>( parent.internalPointer() );
        has = node->numChildren() != 0;
    }
    return has;
}

} } }
