
#include <mutex>
#include <unordered_map>
#include <algorithm>

#include "../common/Threading.h"
#include "../common/ContainerOperations.h"
#include "../common/Constants.h"
#include "Parameters.h"
#include "MessageCenter.h"

namespace Vq {

class MessageCenter::Impl
{
public:
    inline void subscribe( const std::string &messageType,
                           IMessageClient *sub )
    {
        if( sub != nullptr ) {
            VQ_LOCK( m_mutex );
            m_subscribers.insert( std::make_pair( messageType, sub ));
            m_clients.insert( std::make_pair( sub->messageClientId(), sub ));
        }
    }

    inline void subscribe( const std::vector< std::string > &messageTypes,
                           IMessageClient *sub )
    {
        if( sub != nullptr ) {
            VQ_LOCK( m_mutex );
            for( const std::string &msgType : messageTypes ) {
                m_subscribers.insert( std::make_pair( msgType, sub ));
                m_clients.insert( std::make_pair( sub->messageClientId(), sub));
            }
        }
    }

    inline void removeSubscriber( IMessageClient *client )
    {
        if( client != nullptr ) {
            using ValType = decltype( m_subscribers )::value_type;
            VQ_LOCK( m_mutex );
            ContainerOps::eraseIf(
                        m_subscribers,
                        [ &client ]( const ValType &item) -> bool
            {
                return client == item.second;
            });
        }
        else {
            ///TODO log error
        }
    }


    inline void removeSubscriber( const std::string &clientId )
    {
        using ValType = decltype( m_subscribers )::value_type;
        VQ_LOCK( m_mutex );
        ContainerOps::eraseIf(
                    m_subscribers,
                    [ &clientId ]( const ValType &item) -> bool
        {
            return clientId == item.second->messageClientId();
        });

    }


    inline void notify( const IMessageClient *originator,
                        const std::string &messageType,
                        const Parameters &params )
    {
        if( originator != nullptr ) {
            VQ_LOCK( m_mutex );
            auto rangeIt = m_subscribers.equal_range( messageType );
            for( auto it = rangeIt.first; it != rangeIt.second; ++ it ) {
                it->second->onMessage( originator, messageType, params );
            }
        }
        else {
            ///TODO print error ??
        }
    }

private:
    std::unordered_multimap< std::string, IMessageClient * > m_subscribers;

    std::unordered_map< std::string, IMessageClient *> m_clients;

    mutable std::mutex m_mutex;

};


void MessageCenter::destroy()
{
    m_impl.reset( nullptr ); //?
}


const std::string & MessageCenter::uniqueId()
{
    return Constants::EMPTY_STRING;
}


void MessageCenter::subscribe( const std::string &messageType,
                               IMessageClient *sub )
{
    m_impl->subscribe( messageType, sub );
}


void MessageCenter::subscribe( const std::vector< std::string > &messageTypes,
                               IMessageClient *sub )
{
    m_impl->subscribe( messageTypes, sub );
}


void MessageCenter::removeSubscriber( IMessageClient *client )
{
    m_impl->removeSubscriber( client );
}


void MessageCenter::removeSubscriber( const std::string &clientId )
{
    m_impl->removeSubscriber( clientId );
}


void MessageCenter::notify( const IMessageClient *originator,
                            const std::string &messageType,
                            const Parameters &params )
{
    m_impl->notify( originator, messageType, params );
}


}
