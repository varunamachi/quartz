
#include "ViewProvider.h"

namespace Quartz { namespace Plugin { namespace Sample {

const QString SampleView::VIEW_ID{ "qzplugin.sample.view" };
const QString SampleView::VIEW_NAME{ "Sample" };
const QString SampleView::VIEW_CATERGORY{ "sample" };

SampleView::SampleView( QWidget *parent )
    : Quartz::QuartzView(
          SampleView::VIEW_ID,
          SampleView::VIEW_CATERGORY,
          SampleView::VIEW_NAME,
          parent )
{

}

SampleView::~SampleView()
{

}

/***************** Provider **************************************************/
const QString ViewProvider::PLUGIN_ID{ "qzplugin.sample.provider.view" };
const QString ViewProvider::PLUGIN_NAME{ "Quartz Sample View" };
const QStringList ViewProvider::DEPENDENCIES{ };

ViewProvider::ViewProvider()
    : AbstractViewProvider{ PLUGIN_ID, PLUGIN_NAME, DEPENDENCIES }
{

}

ViewProvider::~ViewProvider()
{

}

bool ViewProvider::init()
{
    return true;
}

bool ViewProvider::destroy()
{
    return true;
}

QuartzView * ViewProvider::view() const
{
    return new SampleView{ };
}


} } }
