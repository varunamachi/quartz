
#include <QVBoxLayout>
#include <QTabWidget>

#include <common/iconstore/IconFontStore.h>

#include "PluginConfigPage.h"
#include "DetailsHolder.h"

namespace Quartz { namespace Ext {

const QString PluginConfigPage::CONFIG_PAGE_NAME = QStringLiteral("Plugins");
const QString PluginConfigPage::CONFIG_PAGE_ID = QStringLiteral("qz.plugins");

struct PluginConfigPage::Data
{
    explicit Data(QWidget *parent)
        : m_tabWidget(new QTabWidget(parent))
    {

    }

    QTabWidget *m_tabWidget;
};


PluginConfigPage::PluginConfigPage(QWidget *parent)
    : AbstractConfigPage{ QStringList(),
                          CONFIG_PAGE_NAME,
                          CONFIG_PAGE_ID,
                          getIcon(MatIcon::Extension),
                          parent }
    , m_data(std::make_unique<Data>(this))
{
    auto lyt = new QVBoxLayout();
    lyt->addWidget(m_data->m_tabWidget);
    this->setLayout(lyt);

    m_data->m_tabWidget->addTab(new DetailsHolder(this), tr("Details"));
}

PluginConfigPage::~PluginConfigPage()
{

}

bool PluginConfigPage::apply()
{
    return true;
}

bool PluginConfigPage::setDefaults()
{
    return true;
}

} }
