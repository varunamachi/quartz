#include <QVBoxLayout>
#include <QLabel>

#include "ContentProvider.h"

namespace Quartz { namespace Plugin { namespace Sample {

const QString SampleContent::CONTENT_ID{ "qzp.sample.content.one" };
const QString SampleContent::CONTENT_NAME{ "Sample" };
const QString SampleContent::CONTENT_KIND{ "sample" };

SampleContent::SampleContent( QWidget *parent )
    : ContentWidget{ CONTENT_ID, CONTENT_NAME, CONTENT_KIND, parent }
{
    auto layout = new QVBoxLayout{ this };
    auto label = new QLabel{ "This is sample content", this };
    layout->addWidget( label );
    this->setLayout( layout );
}


/********************** Provider ************************************/
const QString ContentProvider::PLUGIN_ID{
    "qzp.sample.provider.content" };
const QString ContentProvider::PLUGIN_NAME{
    "Quartz Sample Content" };

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
    widgets.push_back( new SampleContent{} );
    return widgets;
}



} } }
