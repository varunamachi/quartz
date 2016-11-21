#pragma once

#include <QString>

#include "../utils/Macros.h"
#include "AbstractPlugin.h"

namespace Quartz {

QZ_INTERFACE IPluginAdapter
{
    virtual const QString & pluginType() const = 0;

    virtual const QString & pluginAdapterName() const = 0;

    virtual bool handlePlugin( AbstractPlugin *plugin ) = 0;

    virtual bool finalizePlugins() = 0;

};

}
