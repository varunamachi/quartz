
#include "ContentProvider.h"

namespace Quartz { namespace Plugin { namespace Sample {

const QString SampleContent::CONTENT_ID{ "Quartz.Quartz.Content" };
const QString SampleContent::CONTENT_NAME{ "Sample" };
const QString SampleContent::CONTENT_KIND{ "sample" };

SampleContent::SampleContent( QWidget *parent )
    : ContentWidget{ CONTENT_ID, CONTENT_NAME, CONTENT_KIND }
{

}


/********************** Provider ************************************/
const QString ContentProvider::PLUGIN_ID{
    "qzplugin.sample.provider.content" };
const QString ContentProvider::PLUGIN_NAME{
    "Quartz Sample Content" };
const QStringList ContentProvider::DEPENDENCIES{ };

ContentProvider::ContentProvider()
    : AbstractContentProvider{ PLUGIN_ID, PLUGIN_NAME, DEPENDENCIES }
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

ContentWidget * ContentProvider::widget()
{
    return new SampleContent{ };
}



} } }
