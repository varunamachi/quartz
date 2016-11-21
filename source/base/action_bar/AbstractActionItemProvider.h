#pragma once

#include <core/extension_system/AbstractPlugin.h>

#include "../QuartzBase.h"

namespace Quartz {

class QuartzItem;

class QUARTZ_BASE_API AbstractActionItemProvider : public AbstractPlugin
{
public:
    AbstractActionItemProvider( const QString &pluginId,
                                const QString &pluginName,
                                const QStringList &dependencies );

    virtual QuartzItem * actionItem() const = 0;

    const static QString PLUGIN_TYPE;
};

}
