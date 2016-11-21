#pragma once

#include "AbstractPlugin.h"
#include "IPluginAdapter.h"

namespace Quartz {

class AbstractAdapterProvider : public AbstractPlugin
{
public:
    AbstractAdapterProvider( const QString &pluginId,
                             const QString &pluginName,
                             const QStringList &dependencies );

    virtual std::shared_ptr< IPluginAdapter > adapter() const = 0;

    const static QString PLUGIN_TYPE;
};

}
