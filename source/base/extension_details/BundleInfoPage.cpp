
#include "PluginItemModel.h"
#include "BundleInfoPage.h"

namespace Quartz {

struct BundleInfoPage::Data
{
    Data( QWidget *parent )
        : m_bundle{ nullptr }
        , m_pluginModel{ new PluginItemModel{ parent }}
    {

    }

    const AbstractPluginBundle *m_bundle;

    PluginItemModel *m_pluginModel;
};

const QString BundleInfoPage::CONTENT_ID{ "qz.bundlepage" };
const QString BundleInfoPage::CONTENT_NAME{ "Plugin Details" };
const QString BundleInfoPage::CONTENT_KIND{ "qz.info" };

BundleInfoPage::BundleInfoPage( QWidget *parent )
    : ContentWidget{ CONTENT_ID,
                     CONTENT_NAME,
                     CONTENT_KIND,
                     parent }
    , m_data{ new Data{ this }}
{

}

BundleInfoPage::~BundleInfoPage()
{

}

void BundleInfoPage::setBundle( const AbstractPluginBundle *bundle )
{
    m_data->m_bundle = bundle;
}



}

