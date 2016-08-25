#include <QHash>
#include <QDir>

#include "IPlugin.h"
#include "IPluginAdapter.h"
#include "PluginManager.h"

namespace Quartz {

using PluginMap = QHash< QString, std::shared_ptr< IPlugin >>;
using AdapterMap = QHash< std::string, std::shared_ptr< IPluginAdapter >>;

class PluginManager::Data
{

private:
    PluginMap & plugins()
    {
        return m_plugins;
    }

    const PluginMap & plugins() const
    {
        return m_plugins;
    }

    AdapterMap & adapters()
    {
        return m_adapters;
    }

    const AdapterMap & adapters() const
    {
        return m_adapters;
    }

public:
    PluginMap m_plugins;

    AdapterMap m_adapters;
};


PluginManager::PluginManager()
    : m_data( std::make_unique< PluginManager::Data >() )
{

}


PluginManager::~PluginManager()
{

}


bool PluginManager::loadFrom( const QString &location )
{
    QDir dir{ location };

    //list contents of the directory

    //Plugin must in its own directory and should have prefix
    //plugin_<name>.so|dll

    //load the shared library

    //get the symbol for getPlugin and invoke it

    //get the plugin and pass it handler associated with its type

    return false;
}


bool PluginManager::destroy()
{
    return false;
}


IPlugin * PluginManager::plugin() const
{
    return nullptr;
}


IPluginAdapter * PluginManager::adapter() const
{
    return nullptr;
}

void PluginManager::registerPluginAdapter( IPluginAdapter *pluginHost )
{

}

}
