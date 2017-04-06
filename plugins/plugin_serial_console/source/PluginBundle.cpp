#include <base/QzAppContext.h>

#include <core/extension_system/IPluginAdapter.h>

#include "PluginBundle.h"

namespace Quartz { namespace Plugin { namespace SerialConsole {

const QString PluginBundle::BUNDLE_ID{ "qzbundle.serial_console" };
const QString PluginBundle::BUNDLE_NAME{ "Serial Console " };

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
