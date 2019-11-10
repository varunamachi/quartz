#pragma once

#include "../QuartzBase.h"
#include "../general_selector/AbstractGeneralNodeProvider.h"

class AbstractConfigPage;

namespace Quartz {

class QUARTZ_BASE_API AbstractConfigPageProvider : public Ext::Extension {
public:
    AbstractConfigPageProvider(const QString& pluginId,
                               const QString& pluginName);

    ~AbstractConfigPageProvider();

    virtual QVector<AbstractConfigPage*> configPages() const = 0;

    static const QString EXTENSION_TYPE;

private:
};

} // namespace Quartz
