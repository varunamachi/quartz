#pragma once

#include <core/extension_system/IPlugin.h>

#include "../QuartzBase.h"

namespace Quartz {

class QuartzView;

class QUARTZ_BASE_API AbstractViewProvider : public IPlugin
{
public:
    virtual QuartzView * view() const = 0;

    const QString & pluginType() const override
    {
        return PLUGIN_TYPE;
    }

    const static QString PLUGIN_TYPE;
};

}
