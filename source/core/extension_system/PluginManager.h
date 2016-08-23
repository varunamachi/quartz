#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../utils/Macros.h"

namespace Quartz {

QZ_INTERFACE IPlugin;
QZ_INTERFACE IPluginAdapter;

class PluginManager
{
public:
    QZ_NO_COPY( PluginManager );

    bool loadFrom( const std::string &location );

    bool destroy();

    IPlugin * plugin() const;

    IPluginAdapter * adapter() const;

    void registerPluginAdapter( IPluginAdapter *pluginHost );

private:
    class Data;
    std::unique_ptr< Data > m_impl;

};

}
