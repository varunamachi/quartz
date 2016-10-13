
#pragma once

#include <core/extension_system/IPlugin.h>

#include "../QuartzBase.h"

namespace Quartz {

class AbstractSelector;

class QUARTZ_BASE_API AbstractSelectorProvider : public IPlugin
{
public:
    virtual AbstractSelector * selector() const = 0;

    const QString & pluginType() const override
    {
        return PLUGIN_TYPE;
    }

    static const QString PLUGIN_TYPE;

private:
};

}
