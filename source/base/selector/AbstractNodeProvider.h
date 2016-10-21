#pragma once

#include <core/extension_system/IPlugin.h>

#include "../QuartzBase.h"

namespace Quartz {

class AbstractSelector;
class Node;
using NodePtr = std::shared_ptr< Node >;

class QUARTZ_BASE_API AbstractNodeProvider : public IPlugin
{
public:
    virtual QPair< QString, NodePtr > node() const = 0;

    const QString & pluginType() const override
    {
        return PLUGIN_TYPE;
    }

    static const QString PLUGIN_TYPE;

private:
};

}
