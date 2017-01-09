
#include <QVBoxLayout>
#include <QLabel>

#include "ViewProvider.h"

namespace Quartz { namespace Plugin { namespace Sample {

const QString SampleView::VIEW_ID{ "qzp.sample.view" };
const QString SampleView::VIEW_NAME{ "Sample" };
const QString SampleView::VIEW_CATERGORY{ "sample" };

SampleView::SampleView( QWidget *parent )
    : Quartz::QuartzView(
          SampleView::VIEW_ID,
          SampleView::VIEW_CATERGORY,
          SampleView::VIEW_NAME,
          parent )
{
    auto layout = new QVBoxLayout{ this };
    auto label = new QLabel{ "This is sample view", this };
    layout->addWidget( label );
    this->setLayout( layout );
}

SampleView::~SampleView()
{

}

/***************** Provider **************************************************/
const QString ViewProvider::PLUGIN_ID{ "qzp.sample.provider.view" };
const QString ViewProvider::PLUGIN_NAME{ "Quartz Sample View" };

ViewProvider::ViewProvider()
    : AbstractViewProvider{ PLUGIN_ID, PLUGIN_NAME }
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

QVector< QuartzView *> ViewProvider::views() const
{
    QVector< QuartzView *> views;
    views.push_back( new SampleView{} );
    return views;
}


} } }
