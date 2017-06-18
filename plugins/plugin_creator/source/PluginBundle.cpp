#include <base/QzAppContext.h>

#include <core/extension_system/IPluginAdapter.h>

#include "ContentProvider.h"
#include "NodeProvider.h"
#include "PluginBundle.h"
#include "TemplateManager.h"

namespace Quartz { namespace Plugin { namespace Creator {

const QString PluginBundle::BUNDLE_ID{ "qzbundle.creator" };
const QString PluginBundle::BUNDLE_NAME{ "Creator Bundle" };

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
    auto np = std::make_shared< NodeProvider >() ;
    auto tman = std::make_shared< TemplateManager >();
    auto cp = std::make_shared< ContentProvider >( tman);

    m_data->m_plugins.push_back( np );
    m_data->m_plugins.push_back( cp );

    m_data->m_adapters.push_back( tman );
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
