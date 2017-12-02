#pragma once

#include <core/ext/Extension.h>

#include "../QuartzBase.h"

namespace Quartz {

class QuartzItem;

class QUARTZ_BASE_API AbstractTitleItemProvider : public Ext::Extension
{
public:
    AbstractTitleItemProvider( const QString &pluginId,
                               const QString &pluginName );

    virtual QVector< QuartzItem *> titleItems() const = 0;

    const static QString EXTENSION_TYPE;
};

}
