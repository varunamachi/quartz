
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLibrary>
#include <QHeaderView>

#include <core/ext/Plugin.h>
#include <core/ext/PluginManager.h>
#include <common/widgets/QzTreeView.h>

#include "../QzAppContext.h"
#include "PluginItemModel.h"
#include "ExtensionItemModel.h"
#include "AdapterItemModel.h"
#include "PluginInfoPage.h"

namespace Quartz { namespace Ext {

struct PluginInfoPage::Data {
    Data(QWidget* parent)
        : m_plugin(nullptr)
        , m_extModel(new ExtensionItemModel(parent))
        , m_adapterModel(new AdapterItemModel(parent))
        , m_pluginModel{new PluginItemModel{PluginItemModel::NumCols::Two,
                                            parent}}
        , m_extView(new QzTreeView(parent))
        , m_adapterView(new QzTreeView(parent))
        , m_dependencyView(new QzTreeView(parent))
        , m_pluginId(new QLineEdit(parent))
        , m_pluginName(new QLineEdit(parent))
        , m_libName(new QLineEdit(parent)) {
        m_extView->setModel(m_extModel);
        m_adapterView->setModel(m_adapterModel);
        m_dependencyView->setModel(m_pluginModel);
        m_extView->setRootIsDecorated(false);
        m_adapterView->setRootIsDecorated(false);
        m_dependencyView->setRootIsDecorated(false);
        m_extView->setContentsMargins(QMargins{});
        m_dependencyView->setContentsMargins(QMargins{});
        m_extView->header()->setSectionResizeMode(
            1, QHeaderView::ResizeToContents);

        m_pluginName->setReadOnly(false);
        m_pluginId->setReadOnly(false);
        m_libName->setReadOnly(false);
    }

    const Plugin* m_plugin;

    ExtensionItemModel* m_extModel;

    AdapterItemModel* m_adapterModel;

    PluginItemModel* m_pluginModel;

    QzTreeView* m_extView;

    QzTreeView* m_adapterView;

    QzTreeView* m_dependencyView;

    QLineEdit* m_pluginId;

    QLineEdit* m_pluginName;

    QLineEdit* m_libName;

    QVector<const Plugin*> m_deps;
};

const QString PluginInfoPage::CONTENT_ID{"qz.pluginpage"};
const QString PluginInfoPage::CONTENT_NAME("Plugin Details");
const QString PluginInfoPage::CONTENT_KIND{"qz.info"};

PluginInfoPage::PluginInfoPage(QWidget* parent)
    : ContentWidget(CONTENT_ID, CONTENT_NAME, CONTENT_KIND, parent)
    , m_data(std::make_unique<Data>(this)) {

    auto infoLayout = new QGridLayout{};
    infoLayout->addWidget(new QLabel(tr("Plugin Name"), this), 0, 0);
    infoLayout->addWidget(m_data->m_pluginName, 0, 1);
    infoLayout->addWidget(new QLabel(tr("Plugin Id"), this), 1, 0);
    infoLayout->addWidget(m_data->m_pluginId, 1, 1);
    infoLayout->addWidget(new QLabel(tr("Plugin Library"), this), 2, 0);
    infoLayout->addWidget(m_data->m_libName, 2, 1);

    auto hlyt = new QGridLayout{};
    hlyt->addWidget(new QLabel(tr("Exported Adapters: ")), 0, 0);
    hlyt->addWidget(m_data->m_adapterView, 1, 0);
    hlyt->addWidget(new QLabel(tr("Plugin Dependencies: ")), 0, 1);
    hlyt->addWidget(m_data->m_dependencyView, 1, 1);

    auto layout = new QVBoxLayout{};
    layout->addLayout(infoLayout);
    layout->addWidget(new QLabel(tr("Exported Extensions")));
    layout->addWidget(m_data->m_extView);
    layout->addLayout(hlyt);
    this->setLayout(layout);
}

PluginInfoPage::~PluginInfoPage() {
}

void PluginInfoPage::setPlugin(const Ext::Plugin* plugin) {
    if (plugin == nullptr) {
        return;
    }
    auto lib = appContext()->pluginManager()->libraryForPlugin(
        plugin->pluginId());
    m_data->m_pluginId->setText(plugin->pluginId());
    m_data->m_pluginName->setText(plugin->pluginName());
    m_data->m_libName->setText(lib != nullptr ? lib->fileName() : "NA");
    m_data->m_plugin = plugin;
    m_data->m_deps.clear();
    const auto& depIds = plugin->dependencies();
    for (int i = 0; i < depIds.size(); ++i) {
        auto dep = appContext()->pluginManager()->plugin(depIds.at(i).first);
        if (dep != nullptr) {
            m_data->m_deps.push_back(dep);
        }
    }
    m_data->m_extModel->setExtensionList(&plugin->extensions());
    m_data->m_adapterModel->setAdapterList(&plugin->adapters());
    m_data->m_pluginModel->setPluginList(&m_data->m_deps);
}

}} // namespace Quartz::Ext
