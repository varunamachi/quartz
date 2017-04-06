#include <QVBoxLayout>
#include <QLabel>

#include "ContentProvider.h"
#include "MainWidget.h"

namespace Quartz { namespace Plugin { namespace SerialConsole {

/********************** Provider ************************************/
const QString ContentProvider::PLUGIN_ID{
    "qzp.serial_console.provider.content" };
const QString ContentProvider::PLUGIN_NAME{
    "Serial Console Content" };

ContentProvider::ContentProvider()
    : AbstractContentProvider{ PLUGIN_ID, PLUGIN_NAME }
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
    widgets.push_back( new MainWidget{ });
    return widgets;
}



} } }
