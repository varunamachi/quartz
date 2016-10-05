#pragma once

#include <core/extension_system/IPlugin.h>

namespace Quartz {

class QuartzPage;

class AbstractPageProvider : public IPlugin
{
public:
    virtual QuartzPage * page() const = 0;

    const QString & pluginType() const override
    {
        return PLUGIN_TYPE;
    }

    const static QString PLUGIN_TYPE;
};

}
