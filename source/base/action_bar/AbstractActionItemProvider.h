#pragma once

#include <core/extension_system/AbstractPlugin.h>

#include "../QuartzBase.h"

namespace Quartz {

class QuartzItem;

class QUARTZ_BASE_API AbstractActionItemProvider : public AbstractPlugin
{
public:
    AbstractActionItemProvider( const QString &pluginId,
                                const QString &pluginName );

    virtual QVector< QuartzItem * > actionItems() const = 0;

    const static QString PLUGIN_TYPE;
};

}
