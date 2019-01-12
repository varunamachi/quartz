
#include <QVBoxLayout>
#include <QTreeView>
#include <QItemSelectionModel>
#include <QHeaderView>

#include <core/ext/Plugin.h>
#include <core/ext/PluginManager.h>

#include <common/iconstore/IconFontStore.h>

#include "../QzAppContext.h"
#include "../content_manager/ContentManager.h"
#include "PluginInfoPage.h"
#include "PluginItemModel.h"
#include "PluginSelector.h"


namespace Quartz { namespace Ext {

struct PluginSelector::Data
{
    explicit Data(QWidget *parent)
        : m_pluginModel{ new PluginItemModel{ PluginItemModel::NumCols::One,
                                              parent }}
        , m_pluginView(new QTreeView(parent))
        , m_content(new PluginInfoPage(parent))
    {
        m_pluginView->setRootIsDecorated(false);
        m_pluginView->header()->setVisible(false);
        m_pluginView->setSelectionBehavior(
                    QAbstractItemView::SelectRows);
        m_pluginView->setSelectionMode(
                    QAbstractItemView::SingleSelection);

    }

    PluginItemModel *m_pluginModel;

    QTreeView *m_pluginView;

    PluginInfoPage *m_content;

    QVector< const Ext::Plugin *> m_plugins;
};

const QString PluginSelector::SELECTOR_ID{ "qz.plugin_selector" };
const QString PluginSelector::SELECTOR_NAME("PLUGINS");


PluginSelector::PluginSelector(QWidget *parent)
    : AbstractSelector{
          SELECTOR_ID,
          SELECTOR_NAME,
          getNormalIcon(MatIcon::Extension),
          getActiveIcon(MatIcon::Extension),
          parent }
    , m_data(std::make_unique<Data>(this))
{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_data->m_pluginView);
    this->setLayout(layout);

    layout->setContentsMargins(QMargins{});
//    m_data->m_pluginView->setContentsMargins(QMargins{});
    this->setContentsMargins(QMargins{});

    appContext()->contentManager()->addContent(m_data->m_content);
    m_data->m_plugins = appContext()->pluginManager()->plugins();
    m_data->m_pluginModel->setPluginList(&m_data->m_plugins);
    m_data->m_pluginView->setModel(m_data->m_pluginModel);
    connect(m_data->m_pluginView->selectionModel(),
             &QItemSelectionModel::currentChanged,
             this,
             &PluginSelector::onSelected);
}

PluginSelector::~PluginSelector()
{
    m_data->m_pluginModel->clear();
}

void PluginSelector::selected()
{
    const auto &selectionModel = m_data->m_pluginView->selectionModel();
    if (selectionModel->hasSelection()) {
        auto index = selectionModel->currentIndex();
        onSelected(index, QModelIndex{});
    }
    else {
        if (m_data->m_pluginModel->rowCount(QModelIndex{}) != 0) {
            auto index = m_data->m_pluginModel->index(0, 0, QModelIndex{});
            selectionModel->setCurrentIndex(
                        index,
                        QItemSelectionModel::SelectCurrent);
        }
    }
}

void PluginSelector::unselected()
{

}

void PluginSelector::onSelected(const QModelIndex &index,
                                 const QModelIndex &/*previous*/)
{
    appContext()->contentManager()->selectContent(PluginInfoPage::CONTENT_ID);
    auto plugin = static_cast< Plugin *>(index.internalPointer());
    if (plugin != nullptr) {
        m_data->m_content->setPlugin(plugin);
    }
}


} }
