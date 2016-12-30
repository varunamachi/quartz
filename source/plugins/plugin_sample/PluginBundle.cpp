#include <base/QzAppContext.h>

#include "Sample.h"
#include "ViewProvider.h"
#include "ContentProvider.h"
#include "NodeProvider.h"
#include "TitleItemProvider.h"
#include "PluginBundle.h"

namespace Quartz { namespace Plugin { namespace Sample {

const QString PluginBundle::BUNDLE_ID{ "qzplugin.sample" };
const QString PluginBundle::BUNDLE_NAME{ "Sample Bundle" };

struct PluginBundle::Data
{
//    PluginList m_pluginList;
    QVector< QString > m_dependencies;
};

PluginList PluginBundle::plugins() const
{
    QVector< std::shared_ptr< AbstractPlugin >> plugins;
    plugins.push_back( std::make_shared< ViewProvider >() );
    plugins.push_back( std::make_shared< ContentProvider >() );
    plugins.push_back( std::make_shared< NodeProvider >() );
    plugins.push_back( std::make_shared< TitleItemProvider >() );
    return plugins;
}

PluginBundle::~PluginBundle()
{

}

const QVector< QString > & PluginBundle::dependencies(
        DependencyType /*depType*/ ) const
{
    return m_data->m_dependencies;
}

PluginBundle::PluginBundle()
    : Quartz::AbstractPluginBundle{ BUNDLE_ID, BUNDLE_NAME }
    , m_data{ new Data{ }}
{

}

} } }
