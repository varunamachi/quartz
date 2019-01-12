#pragma once

#include <core/ext/Extension.h>

namespace Quartz {

class QuartzPage;

class AbstractPageProvider : public Ext::Extension
{
public:
    AbstractPageProvider(const QString &extensionId,
                          const QString &extensionName);

    virtual QVector< QuartzPage *> pages() const = 0;

    const static QString EXTENSION_TYPE;
};

}
