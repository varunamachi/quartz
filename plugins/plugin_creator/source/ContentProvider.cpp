#include <QVBoxLayout>
#include <QLabel>

#include "ContentProvider.h"

namespace Quartz { namespace Plugin { namespace Creator {

const QString Content::CONTENT_ID{ "qzp.creator.content.main" };
const QString Content::CONTENT_NAME{ "Plugin Creator" };
const QString Content::CONTENT_KIND{ "creator" };

Content::Content( QWidget *parent )
    : ContentWidget{ CONTENT_ID, CONTENT_NAME, CONTENT_KIND, parent }
{
    auto layout = new QVBoxLayout{ this };
    layout->addWidget(new QLabel{ "-- -- --" });
    this->setLayout( layout );
}


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
    widgets.push_back( new Content{} );
    return widgets;
}



} } }
