#include <base/QzAppContext.h>

#include <core/extension_system/IPluginAdapter.h>

#include "ContentProvider.h"
#include "PluginBundle.h"

namespace Quartz { namespace OrekClient {

const QString PluginBundle::BUNDLE_ID{ "qzbundle.orek_client" };
const QString PluginBundle::BUNDLE_NAME{ "Orek Client Bundle" };

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
    m_data->m_plugins.push_back( std::make_shared< ContentProvider >() );
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


} }
