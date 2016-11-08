#pragma once

#include <core/extension_system/IPlugin.h>

#include "../QuartzBase.h"

namespace Quartz {

class QuartzItem;

class QUARTZ_BASE_API AbstractTitleItemProvider : public IPlugin
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
