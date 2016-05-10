
#include <quartz_core/QuartzContext.h>

#include "PagePlugin.h"

namespace Vam {

const QString PagePlugin::PLUGIN_ID( "Vam::Sample::PagePlugin" );


QString PagePlugin::pluginId() const
{
    return PLUGIN_ID;
}


Result< bool > PagePlugin::init( Quartz::QuartzContext &context )
{
    context.pageManager().addPage( m_samplePage.get() );
    return Result< bool >::success();
}


Result< bool >PagePlugin::uninit( Quartz::QuartzContext &context ) {
    context.pageManager().removePage( m_samplePage.get() );
    return Result< bool >::success();
}


////Sample page
const QString SamplePage::PAGE_ID( "the_page" );
const QString SamplePage::PAGE_CATEGORY( "sample" );
const QString SamplePage::PAGE_CATEGORY_NAME( "Sample" );
const QString SamplePage::PAGE_DISPLAY_NAME( "Welcome" );

SamplePage::SamplePage( QWidget * /*parent*/ )
    : QuartzPage( PAGE_ID,
                  PAGE_CATEGORY,
                  PAGE_CATEGORY_NAME,
                  PAGE_DISPLAY_NAME,
                  nullptr )
{

}

}
