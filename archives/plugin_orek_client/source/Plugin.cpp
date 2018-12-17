#include <base/QzAppContext.h>

#include <core/ext/IExtensionAdapter.h>

#include "ContentProvider.h"
#include "NodeProvider.h"
#include "Plugin.h"

namespace Quartz { namespace Ext { namespace Orek {

const QString Plugin::PLUGIN_ID{ "qzplugin.orek_client" };
const QString Plugin::PLUGIN_NAME{ "Orek Client" };

struct Plugin::Data
{
    AdapterList m_adapters;
    ExtensionList m_plugins;
    DependencyList m_dependencies;

};

Plugin::Plugin()
    : Quartz::Ext::Plugin{ PLUGIN_ID, PLUGIN_NAME }
    , m_data{ new Data{} }
{
    m_data->m_plugins.push_back( std::make_shared< ContentProvider >() );
    m_data->m_plugins.push_back( std::make_shared< NodeProvider >() );

}

Plugin::~Plugin()
{

}

const ExtensionList & Plugin::extensions() const
{
    return m_data->m_plugins;
}


const DependencyList & Plugin::dependencies() const
{
    return m_data->m_dependencies;
}

const AdapterList &Plugin::adapters() const
{
    return m_data->m_adapters;
}


} } }
