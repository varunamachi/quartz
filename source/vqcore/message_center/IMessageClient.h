#pragma once

#include "../VQ.h"

#include "Parameters.h"

namespace Vam {

VQ_INTERFACE IMessageClient
{
    virtual std::string messageClientId() const = 0;

    virtual void onMessage( const IMessageClient *originator,
                            const std::string &messageType,
                            const Parameters &params ) = 0;
};


}
