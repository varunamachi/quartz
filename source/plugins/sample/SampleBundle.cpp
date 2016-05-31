#include "SampleBundle.h"

namespace Vq {

const QString SampleBundle::BUNDLE_ID( "Vq::SampleBundle" );
const QString SampleBundle::BUNDLE_NAME( "Sample Bundle" );

SampleBundle::SampleBundle()
    : Quartz::PluginBundle( SampleBundle::BUNDLE_ID,
                            SampleBundle::BUNDLE_NAME )
{

}


}
