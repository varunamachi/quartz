
#include <QVBoxLayout>
#include <QTabWidget>

#include <common/iconstore/IconFontStore.h>

#include "ConfigPage.h"

namespace Quartz { namespace Ext { namespace WebTech {

const QString ConfigPage::CONFIG_PAGE_NAME = QStringLiteral("WebTech");
const QString ConfigPage::CONFIG_PAGE_ID = QStringLiteral("qzp.webtech.config");

struct ConfigPage::Data
{
    explicit Data(QWidget *parent)
        : m_tabWidget(new QTabWidget(parent))
    {

    }

    QTabWidget *m_tabWidget;
};

ConfigPage::ConfigPage(QWidget *parent)
    : AbstractConfigPage(
          {},
          CONFIG_PAGE_NAME,
          CONFIG_PAGE_ID,
          getIcon(FAIcon::PencilAlt),
          parent)
    , m_data(std::make_unique<Data>(this))
{
    auto lyt = new QVBoxLayout();
    lyt->addWidget(m_data->m_tabWidget);
    this->setLayout(lyt);
}

ConfigPage::~ConfigPage()
{

}

bool ConfigPage::apply()
{
    return true;
}

bool ConfigPage::setDefaults()
{
    return true;
}

} } }
