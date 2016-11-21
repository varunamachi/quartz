#pragma once

#include <core/extension_system/AbstractPlugin.h>

namespace Quartz {

class QuartzPage;

class AbstractPageProvider : public AbstractPlugin
{
public:
    AbstractPageProvider( const QString &pluginId,
                          const QString &pluginName,
                          const QStringList &dependencies );

    virtual QuartzPage * page() const = 0;

    const static QString PLUGIN_TYPE;
};

}
