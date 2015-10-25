#pragma once

#include <vqcore/VQ.h>

#include "Parameters.h"
#include "QuartzCore.h"

namespace Vam { namespace Quartz {

VQ_INTERFACE QZ_CORE_EXPORT IMessageClient
{
    virtual QString messageClientId() const = 0;

    virtual void onMessage( const IMessageClient *originator,
                            const QString &messageType,
                            const Parameters &params ) = 0;
};


} }
