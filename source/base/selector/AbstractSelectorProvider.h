
#pragma once

#include <core/extension_system/AbstractPlugin.h>

#include "../QuartzBase.h"

namespace Quartz {

class AbstractSelector;

class QUARTZ_BASE_API AbstractSelectorProvider : public AbstractPlugin
{
public:
    AbstractSelectorProvider( const QString &pluginId,
                              const QString &pluginName );

    virtual ~AbstractSelectorProvider();

    virtual QList< AbstractSelector *> selectors() const = 0;

    static const QString PLUGIN_TYPE;

private:

};

}
