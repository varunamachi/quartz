#pragma once

#include <core/extension_system/IPluginAdapter.h>

#include "../selector/TreeModel.h"

namespace Quartz {

class QUARTZ_BASE_API ConfigNodeTree : public TreeModel
                                     , public IPluginAdapter
{
    Q_OBJECT

public:
    explicit ConfigNodeTree( QObject *parent = nullptr );

    const QString & pluginType() const override;

    const QString & pluginAdapterName() const override;

    bool handlePlugin( AbstractPlugin *plugin ) override;

    bool finalizePlugins() override;
};



}
