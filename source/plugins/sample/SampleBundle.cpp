#include "SampleBundle.h"

namespace Vam {

const QString SampleBundle::BUNDLE_ID( "Vam::SampleBundle" );
const QString SampleBundle::BUNDLE_NAME( "Sample Bundle" );

SampleBundle::SampleBundle()
    : Quartz::PluginBundle( SampleBundle::BUNDLE_ID,
                            SampleBundle::BUNDLE_NAME )
{

}


}
