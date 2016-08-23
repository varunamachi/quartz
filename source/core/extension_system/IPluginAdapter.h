#pragma once

#include <string>

#include "../utils/Macros.h"
#include "IPlugin.h"

namespace Quartz {

QZ_INTERFACE IPluginAdapter
{
    virtual std::string & pluginType() const = 0;

    virtual std::string & pluginHostName() const = 0;

    virtual bool handlePlugin() = 0;

    virtual bool finalizePlugin() = 0;

};

}
