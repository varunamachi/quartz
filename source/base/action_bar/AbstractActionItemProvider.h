#pragma once

#include <core/ext/Extension.h>

#include "../QuartzBase.h"

namespace Quartz {

class QuartzItem;

class QUARTZ_BASE_API AbstractActionItemProvider : public Ext::Extension {
public:
    AbstractActionItemProvider(const QString& pluginId,
                               const QString& pluginName);

    virtual QVector<QuartzItem*> actionItems() const = 0;

    const static QString EXTENSION_TYPE;
};

} // namespace Quartz
