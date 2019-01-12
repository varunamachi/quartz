#include <QVBoxLayout>
#include <QLabel>

#include "ContentProvider.h"
#include "MainWidget.h"

namespace Quartz { namespace Ext { namespace SerialConsole {

/********************** Provider ************************************/
const QString ContentProvider::EXTENSION_ID{
    "qzp.serial_console.provider.content" };
const QString ContentProvider::EXTENSION_NAME{
    "Serial Console Content" };

ContentProvider::ContentProvider()
    : AbstractContentProvider(EXTENSION_ID, EXTENSION_NAME)
{

}

ContentProvider::~ContentProvider()
{

}

bool ContentProvider::init()
{
    return true;
}

bool ContentProvider::destroy()
{
    return true;
}

QVector< ContentWidget *> ContentProvider::widgets()
{
    QVector< ContentWidget *> widgets;
    widgets.push_back(new MainWidget());
    return widgets;
}



} } }
