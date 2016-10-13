#pragma once

#include <memory>

#include <core/extension_system/IPluginAdapter.h>

#include "AbstractSelector.h"

namespace Quartz {

class NodeSelector : public AbstractSelector
                   , public IPluginAdapter
{
public:
    NodeSelector( QWidget *parent = nullptr );

    ~NodeSelector();

    static const QString SELECTOR_ID;

    static const QString SELECTOR_NAME;

    static const QString ADAPTER_NAME;

    static const QString PLUGIN_TYPE;

public:
    const QString &pluginType() const;

    const QString &pluginAdapterName() const;

    bool handlePlugin(IPlugin *plugin);

    bool finalizePlugins();

private:
    struct Data;
    std::unique_ptr< Data > m_data;


    // IPluginAdapter interface
};



}
