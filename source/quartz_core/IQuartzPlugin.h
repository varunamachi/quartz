#pragma once

#include <vqcore/VQCommon.h>

#include "QuartzContext.h"

namespace Vam { namespace Quartz {

VQ_INTERFACE QZ_CORE_EXPORT  IQuartzPlugin
{
    virtual QString pluginId() const = 0;

    virtual bool init( const QuartzContext &context );

    virtual bool uninit( const QuartzContext &context );

};

} }
