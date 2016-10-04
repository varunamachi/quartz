#pragma once

#include <core/extension_system/IPlugin.h>

namespace Quartz {

class ActionItemProvider : public IPlugin
{
public:
    QString &pluginId() const;
    QString &pluginName() const;
    QString &pluginType() const;
    QStringList &dependencies() const;
    bool init();
    bool destroy();
};

}
