#pragma once

#include "../QuartzBase.h"
#include "../selector/AbstractSelector.h"

namespace Quartz { namespace Ext {

class Plugin;

class QUARTZ_BASE_API PluginSelector : public AbstractSelector {
    Q_OBJECT

public:
    explicit PluginSelector(QWidget* parent = nullptr);

    ~PluginSelector() override;

    void selected() override;

    void unselected() override;

    static const QString SELECTOR_ID;

    static const QString SELECTOR_NAME;

Q_SIGNALS:
    void sigPluginSelected(Plugin* plugin);

private Q_SLOTS:
    void onSelected(const QModelIndex& selcted, const QModelIndex& previous);

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}} // namespace Quartz::Ext
