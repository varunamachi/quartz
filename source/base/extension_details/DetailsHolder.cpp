
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>

#include <core/ext/PluginManager.h>
#include <core/ext/Plugin.h>

#include "../QzAppContext.h"
#include "PluginInfoPage.h"
#include "DetailsHolder.h"

namespace Quartz { namespace Ext {

struct DetailsHolder::Data {
    Data(QWidget* parent)
        : m_infoPage(new PluginInfoPage(parent))
        , m_selector(new QComboBox(parent)) {
    }

    PluginInfoPage* m_infoPage;

    QComboBox* m_selector;

    QVector<const Plugin*> m_plugins;
};

DetailsHolder::DetailsHolder(QWidget* parent)
    : QWidget(parent)
    , m_data(std::make_unique<Data>(this)) {
    auto selectorLayout = new QHBoxLayout();
    auto label = new QLabel(tr("Select Plugin"), this);
    label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    selectorLayout->addWidget(label);
    selectorLayout->addWidget(m_data->m_selector);

    auto lyt = new QVBoxLayout();
    lyt->addLayout(selectorLayout);
    lyt->addWidget(m_data->m_infoPage);
    this->setLayout(lyt);

    m_data->m_plugins = appContext()->pluginManager()->plugins();
    for (const auto& plugin : m_data->m_plugins) {
        m_data->m_selector->addItem(plugin->pluginName(), plugin->pluginId());
    }
    if (m_data->m_plugins.size() > 0) {
        m_data->m_infoPage->setPlugin(m_data->m_plugins[0]);
    }

    connect(m_data->m_selector,
            qOverload<int>(&QComboBox::currentIndexChanged),
            [this](int index) {
                auto plugin = m_data->m_plugins[index];
                m_data->m_infoPage->setPlugin(plugin);
            });
}

DetailsHolder::~DetailsHolder() {
}

}} // namespace Quartz::Ext
