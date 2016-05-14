#pragma once

#include "../VQ.h"

#include "Parameters.h"

namespace Vam {

VQ_INTERFACE IMessageClient
{
    virtual QString messageClientId() const = 0;

    virtual void onMessage( const IMessageClient *originator,
                            const QString &messageType,
                            const Parameters &params ) = 0;
};


}
