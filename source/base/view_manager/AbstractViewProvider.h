#pragma once

#include <core/ext/Extension.h>

#include "../QuartzBase.h"

namespace Quartz {

class QuartzView;

class QUARTZ_BASE_API AbstractViewProvider : public Ext::Extension
{
public:
    AbstractViewProvider( const QString &pluginId,
                          const QString &pluginName );

    virtual QVector< QuartzView *> views() const = 0;

    const static QString EXTENSION_TYPE;
};

}
