#pragma once

#include <core/extension_system/AbstractPlugin.h>

#include "../QuartzBase.h"

namespace Quartz {

class QuartzItem;

class QUARTZ_BASE_API AbstractTitleItemProvider : public AbstractPlugin
{
public:
    AbstractTitleItemProvider( const QString &pluginId,
                               const QString &pluginName,
                               const QStringList &dependencies );

    virtual QuartzItem * titleItem() const = 0;

    const static QString PLUGIN_TYPE;
};

}
