#include <base/QzAppContext.h>

#include <core/extension_system/IPluginAdapter.h>

#include "ViewProvider.h"
#include "ContentProvider.h"
#include "NodeProvider.h"
#include "TitleItemProvider.h"
#include "PluginBundle.h"

namespace Quartz { namespace Plugin { namespace Sample {

const QString PluginBundle::BUNDLE_ID{ "qzbundle.sample" };
const QString PluginBundle::BUNDLE_NAME{ "Sample Bundle" };

struct PluginBundle::Data
{
    AdapterList m_adapters;
    PluginList m_plugins;
    DependencyList m_dependencies;

};

PluginBundle::PluginBundle()
    : Quartz::AbstractPluginBundle{ BUNDLE_ID, BUNDLE_NAME }
    , m_data{ new Data{} }
{
//    m_data->m_plugins.push_back( std::make_shared< ViewProvider >() );
//    m_data->m_plugins.push_back( std::make_shared< ContentProvider >() );
//    m_data->m_plugins.push_back( std::make_shared< NodeProvider >() );
//    m_data->m_plugins.push_back( std::make_shared< TitleItemProvider >() );
}

PluginBundle::~PluginBundle()
{

}

const PluginList & PluginBundle::plugins() const
{
    return m_data->m_plugins;
}


const DependencyList & PluginBundle::dependencies() const
{
    return m_data->m_dependencies;
}

const AdapterList &PluginBundle::adapters() const
{
    return m_data->m_adapters;
}


} } }
