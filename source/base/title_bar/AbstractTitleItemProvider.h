#pragma once

#include <core/extension_system/IPlugin.h>

namespace Quartz {

class QuartzItem;

class AbstractTitleItemProvider : public IPlugin
{
public:
    virtual QuartzItem * titleItem() const = 0;

    const QString & pluginType() const override
    {
        return PLUGIN_TYPE;
    }

    const static QString PLUGIN_TYPE;
};

}
