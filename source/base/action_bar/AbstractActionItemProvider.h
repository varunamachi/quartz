#pragma once

#include <core/extension_system/IPlugin.h>

namespace Quartz {

class QuartzItem;

class AbstractActionItemProvider : public IPlugin
{
public:
    virtual QuartzItem * actionItem() const = 0;

    const QString & pluginType() const override
    {
        return PLUGIN_TYPE;
    }

    const static QString PLUGIN_TYPE;
};

}
