#pragma once

#include <core/extension_system/AbstractPlugin.h>

#include "../QuartzBase.h"

namespace Quartz {

class QuartzView;

class QUARTZ_BASE_API AbstractViewProvider : public AbstractPlugin
{
public:
    AbstractViewProvider( const QString &pluginId,
                          const QString &pluginName,
                          const QStringList &dependencies );

    virtual QuartzView * view() const = 0;

    const static QString PLUGIN_TYPE;
};

}
