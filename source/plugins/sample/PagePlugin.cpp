
#include <quartz_core/QuartzContext.h>

#include "PagePlugin.h"

namespace Vam {

const QString PagePlugin::PLUGIN_ID( "Vam::Sample::PagePlugin" );


QString PagePlugin::pluginId() const
{
    return PLUGIN_ID;
}


void PagePlugin::init( Quartz::QuartzContext &context )
{
    context.pageManager().addPage( m_samplePage.get() );
}


void PagePlugin::uninit( Quartz::QuartzContext &context ) {
    context.pageManager().removePage( m_samplePage.get() );
}


////Sample page
SamplePage::SamplePage( const QString &pageId,
                        const QString &category,
                        const QString &categoryName,
                        const QString &displayName,
                        QWidget *parent )
    : QuartzPage( "the_page",
                  "sample",
                  "Sample",
                  "Sample",
                  nullptr )
{

}

}
