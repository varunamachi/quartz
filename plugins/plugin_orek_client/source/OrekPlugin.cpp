#include <base/QzAppContext.h>

#include <core/ext/IExtensionAdapter.h>

#include "ContentProvider.h"
#include "NodeProvider.h"
#include "OrekPlugin.h"

namespace Quartz { namespace Ext { namespace Orek {

const QString OrekPlugin::PLUGIN_ID{ "qzplugin.orek_client" };
const QString OrekPlugin::PLUGIN_NAME{ "Orek Client" };

struct OrekPlugin::Data
{
    AdapterList m_adapters;
    ExtensionList m_plugins;
    DependencyList m_dependencies;

};

OrekPlugin::OrekPlugin()
    : Quartz::Ext::Plugin{ PLUGIN_ID, PLUGIN_NAME }
    , m_data{ new Data{} }
{
    m_data->m_plugins.push_back( std::make_shared< ContentProvider >() );
    m_data->m_plugins.push_back( std::make_shared< NodeProvider >() );

}

OrekPlugin::~OrekPlugin()
{

}

const ExtensionList & OrekPlugin::extensions() const
{
    return m_data->m_plugins;
}


const DependencyList & OrekPlugin::dependencies() const
{
    return m_data->m_dependencies;
}

const AdapterList &OrekPlugin::adapters() const
{
    return m_data->m_adapters;
}


} } }
