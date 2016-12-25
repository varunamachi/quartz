#pragma once

#include <core/extension_system/IPluginAdapter.h>

#include "../selector/TreeModel.h"

namespace Quartz {

class GeneralNodeTree : public TreeModel
                      , public IPluginAdapter
{
    Q_OBJECT

public:
    explicit GeneralNodeTree( QObject *parent = nullptr );

    const QString & pluginType() const override;

    const QString & pluginAdapterName() const override;

    bool handlePlugin( AbstractPlugin *plugin ) override;

    bool finalizePlugins() override;


};



}
