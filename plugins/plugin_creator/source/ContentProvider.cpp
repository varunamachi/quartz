#include <QVBoxLayout>
#include <QLabel>

#include "ContentProvider.h"
#include "CreatorWidget.h"

namespace Quartz { namespace Plugin { namespace Creator {

/********************** Provider ************************************/
const QString ContentProvider::PLUGIN_ID{
    "qzp.creator.provider.content" };
const QString ContentProvider::PLUGIN_NAME{
    "Quartz Creator Content" };

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
    widgets.push_back( new CreatorWidget{} );
    return widgets;
}



} } }
