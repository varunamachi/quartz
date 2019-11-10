
#pragma once

#include <core/ext/Extension.h>

#include "../QuartzBase.h"

namespace Quartz {

class AbstractSelector;

class QUARTZ_BASE_API AbstractSelectorProvider : public Ext::Extension {
public:
    AbstractSelectorProvider(const QString& pluginId,
                             const QString& pluginName);

    virtual ~AbstractSelectorProvider();

    virtual QList<AbstractSelector*> selectors() const = 0;

    static const QString EXTENSION_TYPE;

private:
};

} // namespace Quartz
