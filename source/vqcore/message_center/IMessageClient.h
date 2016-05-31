#pragma once

#include <string>

#include "../VQ.h"
#include "../common/Macros.h"


namespace Vq {

class Parameters;

VQ_INTERFACE IMessageClient
{
    virtual std::string & messageClientId() const = 0;

    virtual void onMessage( const IMessageClient *originator,
                            const std::string &messageType,
                            const Parameters &params ) = 0;

    virtual ~ IMessageClient() { }
};


}
