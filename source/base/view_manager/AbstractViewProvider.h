#pragma once

#include <core/extension_system/AbstractPlugin.h>

#include "../QuartzBase.h"

namespace Quartz {

class QuartzView;

class QUARTZ_BASE_API AbstractViewProvider : public AbstractPlugin
{
public:
    AbstractViewProvider( const QString &pluginId,
                          const QString &pluginName );

    virtual QVector< QuartzView *> views() const = 0;

    const static QString PLUGIN_TYPE;
};

}
