#pragma once

#include <vector>
#include <memory>

#include "IMessageClient.h"
#include "../common/Macros.h"

namespace Vq {

class VQ_API MessageCenter
{
public:
    void destroy();

    const std::string & uniqueId();

    void subscribe( const std::string &messageType,
                    IMessageClient *sub );

    void subscribe( const std::vector< std::string > &messageTypes,
                    IMessageClient *sub );

    void removeSubscriber( IMessageClient *client );

    void removeSubscriber( const std::string &clientId );

    void notify( const IMessageClient *originator,
                 const std::string &messageType,
                 const Parameters &params );

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;


};

}
