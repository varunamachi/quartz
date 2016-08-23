#pragma once

#include <string>

#include "../utils/Macros.h"

namespace Quartz {

QZ_INTERFACE IPlugin
{
    virtual std::string & pluginId() const = 0;

    virtual std::string & pluginName() const = 0;

    virtual std::string & pluginType() const = 0;

    virtual bool init() = 0;

    virtual bool destroy() = 0;
};

}
