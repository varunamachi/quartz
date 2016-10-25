#pragma once

#include <memory>

#include <QWidget>

#include <core/extension_system/IPluginAdapter.h>

namespace Quartz {

class ContentManager : public QWidget
                     , public IPluginAdapter
{
    Q_OBJECT
public:
    explicit ContentManager( QWidget *parent = nullptr );

    ~ContentManager();

public:
    const QString &pluginType() const override;

    const QString &pluginAdapterName() const override;

    bool handlePlugin(IPlugin *plugin) override;

    bool finalizePlugins() override;

    static const QString ADAPTER_NAME;

public:


private:
    struct Data;
    std::unique_ptr< Data > m_data;


};

}
