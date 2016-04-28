#pragma once

#include <vqcore/VQCommon.h>

#include "QuartzContext.h"

namespace Vam { namespace Quartz {

VQ_INTERFACE IQuartzPlugin
{
    virtual QString pluginId() const = 0;

    virtual bool init( QuartzContext &context ) = 0;

    virtual bool uninit( QuartzContext &context ) = 0;

};

} }
