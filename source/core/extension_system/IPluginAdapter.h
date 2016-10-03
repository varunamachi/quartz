#pragma once

#include <QString>

#include "../utils/Macros.h"
#include "IPlugin.h"

namespace Quartz {

static const char * ADAPTER_PLUGIN_TYPE = "adapter";

QZ_INTERFACE IPluginAdapter
{
    virtual const QString & pluginType() const = 0;

    virtual const QString & pluginAdapterName() const = 0;

    virtual bool handlePlugin( IPlugin *plugin ) = 0;

    virtual bool finalizePlugins() = 0;

};


QZ_INTERFACE IAdapterPlugin : public IPlugin
{
    virtual std::shared_ptr< IPluginAdapter > adapter() = 0;
};


}
