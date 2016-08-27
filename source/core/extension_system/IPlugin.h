#pragma once

#include <memory>

#include <QString>
#include <QStringList>

#include "../utils/Macros.h"

namespace Quartz {



QZ_INTERFACE IPlugin
{
    virtual QString & pluginId() const = 0;

    virtual QString & pluginName() const = 0;

    virtual QString & pluginType() const = 0;

    virtual QStringList & dependencies() const = 0;

    virtual bool init() = 0;

    virtual bool destroy() = 0;
};

}

extern "C" {

struct PluginListWrapper {
    QList< std::shared_ptr< Quartz::IPlugin >>  pluginList;
};

}
