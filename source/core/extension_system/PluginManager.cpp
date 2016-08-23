
#include "IPlugin.h"
#include "IPluginAdapter.h"
#include "PluginManager.h"

namespace Quartz {

bool PluginManager::loadFrom( const std::string &location )
{
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
