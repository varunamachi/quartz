
#pragma once

#include <core/extension_system/IPlugin.h>

namespace Quartz {

class AbstractSelector;

class AbstractSelectorProvider : public IPlugin
{
public:
    virtual AbstractSelector selector() const = 0;

    const QString & pluginType() const override
    {
        return PLUGIN_TYPE;
    }

    static const PLUGIN_TYPE;

private:
};

}
