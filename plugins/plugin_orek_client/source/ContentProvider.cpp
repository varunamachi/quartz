#include <QVBoxLayout>
#include <QLabel>

#include "ContentProvider.h"

namespace Quartz { namespace OrekClient {

const QString SampleContent::CONTENT_ID{ "qzp.orekclient.content" };
const QString SampleContent::CONTENT_NAME{ "Orek" };
const QString SampleContent::CONTENT_KIND{ "orek" };

SampleContent::SampleContent( QWidget *parent )
    : ContentWidget{ CONTENT_ID, CONTENT_NAME, CONTENT_KIND, parent }
{
    auto layout = new QVBoxLayout{ this };
    auto label = new QLabel{ "O.R.E.K", this };
    layout->addWidget( label );
    this->setLayout( layout );
}


/********************** Provider ************************************/
const QString ContentProvider::PLUGIN_ID{
    "qzp.orekclient.provider.content" };
const QString ContentProvider::PLUGIN_NAME{
    "Orek Content" };

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



} }
