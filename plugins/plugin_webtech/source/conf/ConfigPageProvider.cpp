
#include "ConfigPage.h"
#include "ConfigPageProvider.h"

namespace Quartz { namespace Ext { namespace WebTech {

const QString ConfigPageProvider::PLUGIN_ID =
        QStringLiteral("qzp.webtech.provider.config");
const QString ConfigPageProvider::PLUGIN_NAME =
        QStringLiteral("WebTech Config Pages");


struct ConfigPageProvider::Data
{
    Data() {
        m_pages.append(new ConfigPage());
    }
    QVector<AbstractConfigPage *> m_pages;
};

ConfigPageProvider::ConfigPageProvider()
    : AbstractConfigPageProvider(PLUGIN_ID, PLUGIN_NAME)
    , m_data(std::make_unique<Data>())
{

}

ConfigPageProvider::~ConfigPageProvider()
{

}

QVector<AbstractConfigPage *> ConfigPageProvider::configPages() const
{
    return m_data->m_pages;
}

} } }
