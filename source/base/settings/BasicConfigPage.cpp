
#include <QIcon>

#include <common/iconstore/IconFontStore.h>

#include "BasicConfigPage.h"

namespace Quartz {

const QString BasicConfigPage::CONFIG_PAGE_ID{ "qz.configpage.basic" };
const QString BasicConfigPage::CONFIG_PAGE_NAME{ "Basic Settings" };

struct BasicConfigPage::Data
{

};

BasicConfigPage::BasicConfigPage( QWidget *parent )
    : AbstractConfigPage{ QStringList{ },
                          CONFIG_PAGE_NAME,
                          CONFIG_PAGE_ID,
                          getIcon(MatIcon::SettingsApplications),
                          parent }
    , m_data{ new Data{} }
{

}

BasicConfigPage::~BasicConfigPage()
{

}

bool BasicConfigPage::apply()
{
    return false;
}

bool BasicConfigPage::setDefaults()
{
    return false;
}




}
