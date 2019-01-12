#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QFile>

#include <plugin_base/PluginLogging.h>

#include "TitleItemProvider.h"


namespace Quartz { namespace Ext { namespace Sample {

const QString TitleBarButton::ITEM_ID{ "qzp.sample.titlebutton" };
const QString TitleBarButton::ITEM_CATERGORY("sample");

TitleBarButton::TitleBarButton(QWidget *parent)
    : Quartz::QuartzItem(
          TitleBarButton::ITEM_ID,
          TitleBarButton::ITEM_CATERGORY,
          parent)
{
    auto layout = new QVBoxLayout(this);
    auto pushButton = new QPushButton{ /*tr("sample"),*/ this };
    pushButton->setIcon(QIcon(":chilli"));
    pushButton->setFlat(true);
//    QFile file{ ":/chilli" };
//    QZP_INFO << (file.exists() ? "Exists" : "Does not exist");
//    layout->addWidget(pushButton);
//    layout->setContentsMargins(QMargins{});
    this->setLayout(layout);
    this->setContentsMargins(QMargins{});

    connect(pushButton,
             &QPushButton::clicked,
             []() {
//       qDebug() << "Hello!!";
        QZP_INFO << "Hello!!";
    });
}

TitleBarButton::~TitleBarButton()
{

}

/***************** Provider **************************************************/
const QString TitleItemProvider::EXTENSION_ID{
    "qzp.sample.provider.titlebutton" };
const QString TitleItemProvider::EXTENSION_NAME{
    "Quartz Sample TitleBar Button" };


TitleItemProvider::TitleItemProvider()
    : AbstractTitleItemProvider(EXTENSION_ID, EXTENSION_NAME)
{

}

TitleItemProvider::~TitleItemProvider()
{

}

bool TitleItemProvider::init()
{
    return true;
}

bool TitleItemProvider::destroy()
{
    return true;
}

QVector< QuartzItem *> TitleItemProvider::titleItems() const
{
    QVector< QuartzItem *> items;
    items.push_back(new TitleBarButton{});
    return items;
}


} } }
