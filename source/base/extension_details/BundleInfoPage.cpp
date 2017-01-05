
#include "BundleInfoPage.h"

namespace Quartz {

struct BundleInfoPage::Data
{

};

const QString BundleInfoPage::CONTENT_ID{ "qz.bundlepage" };
const QString BundleInfoPage::CONTENT_NAME{ "Plugin Details" };
const QString BundleInfoPage::CONTENT_KIND{ "qz.info" };

BundleInfoPage::BundleInfoPage( QWidget *parent )
    : ContentWidget{ CONTENT_ID,
                     CONTENT_NAME,
                     CONTENT_KIND,
                     parent }
    , m_data{ new Data{ }}
{

}

BundleInfoPage::~BundleInfoPage()
{

}



}

