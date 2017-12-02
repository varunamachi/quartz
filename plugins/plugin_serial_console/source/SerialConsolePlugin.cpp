#include <base/QzAppContext.h>

#include <core/ext/IExtensionAdapter.h>

#include "Constants.h"
#include "ContentProvider.h"
#include "NodeProvider.h"
#include "SerialConsolePlugin.h"

namespace Quartz { namespace Ext { namespace SerialConsole {

const QString SerialConsolePlugin::PLUGIN_ID{ "qzplugin.serial_console" };
const QString SerialConsolePlugin::PLUGIN_NAME{ "Serial Console " };

struct SerialConsolePlugin::Data
{
    AdapterList m_adapters;
    ExtensionList m_plugins;
    DependencyList m_dependencies;
};

SerialConsolePlugin::SerialConsolePlugin()
    : Quartz::Ext::Plugin{ PLUGIN_ID, PLUGIN_NAME }
    , m_data{ new Data{} }
{
    m_data->m_plugins.push_back( std::make_shared< ContentProvider >() );
    m_data->m_plugins.push_back( std::make_shared< NodeProvider >() );
}

SerialConsolePlugin::~SerialConsolePlugin()
{

}

const ExtensionList & SerialConsolePlugin::extensions() const
{
    return m_data->m_plugins;
}


const DependencyList & SerialConsolePlugin::dependencies() const
{
    return m_data->m_dependencies;
}

const AdapterList &SerialConsolePlugin::adapters() const
{
    return m_data->m_adapters;
}


} } }
