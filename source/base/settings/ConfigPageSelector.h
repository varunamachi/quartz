
#pragma once

#include <core/extension_system/IPluginAdapter.h>

#include "../QuartzBase.h"
#include "../selector/AbstractSelector.h"

namespace Quartz {

class Node;
class TreeModel;
class AbstractConfigPage;

class QUARTZ_BASE_API ConfigPageSelector : public AbstractSelector
                                         , public IPluginAdapter
{
    Q_OBJECT

public:
    explicit ConfigPageSelector( QWidget *parent = nullptr );

    ~ConfigPageSelector();

    TreeModel * model();

    void selected() override;

    void unselected() override;

    static const QString SELECTOR_ID;

    static const QString SELECTOR_NAME;

public:
    const QString &pluginType() const override;

    const QString &pluginAdapterName() const override;

    bool handlePlugin( AbstractPlugin *plugin) override;

    bool finalizePlugins() override;

    bool addPage( AbstractConfigPage *page );

    static const QString ADAPTER_NAME;

signals:
    void sigConfigNodeSelected( const Node *node );

private slots:
    void onSelected( const QModelIndex &current,
                     const QModelIndex &previous );

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
