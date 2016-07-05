
#include <vqcore/common/Result.h>

#include <quartz_core/QuartzContext.h>

#include "PagePlugin.h"

namespace Vq {

const QString PagePlugin::PLUGIN_ID( "Vq::Sample::PagePlugin" );


QString PagePlugin::pluginId() const
{
    return PLUGIN_ID;
}


Result< bool > PagePlugin::init( Quartz::QuartzContext &context )
{
    context.pageManager().addPage( m_samplePage.get() );
    return R::success< bool >( true );
}


Result< bool > PagePlugin::uninit( Quartz::QuartzContext &context ) {
    context.pageManager().removePage( m_samplePage.get() );
    return R::success< bool >( true );
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
