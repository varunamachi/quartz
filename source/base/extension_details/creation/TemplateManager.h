#pragma once

#include <memory>

#include <QList>

#include <core/extension_system/IPluginAdapter.h>


namespace Quartz {

class Template;

class TemplateManager : public IPluginAdapter
{
public:
    explicit TemplateManager();

    ~TemplateManager();

    void addTemplate( std::shared_ptr< Template> tmplt );

    QList< Template *> templates() const;

    const QString &pluginType() const;

    const QString &pluginAdapterName() const;

    bool handlePlugin(AbstractPlugin *plugin);

    bool finalizePlugins();

    static const QString ADAPTER_NAME;

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};


}
