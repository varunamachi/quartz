#pragma once

#include <QHash>
#include <QReadWriteLock>
#include <QObject>

#include "IMessageClient.h"

namespace Vam {

class VQ_CORE_EXPORT MessageCenter : public QObject
{
    Q_OBJECT
public:
    void destroy();

    const std::string & uniqueId();

public slots:
    void subscribe( const std::string &messageType,
                    IMessageClient *sub );

    void subscribe( const std::stringList &messageTypes,
                    IMessageClient *sub );

    void removeSubscriber( IMessageClient *client );

    void removeSubscriber( const std::string &clientId );

    void notify( const IMessageClient *originator,
                 const std::string &messageType,
                 const Parameters &params );

signals:
    void onNotify( const IMessageClient *originator,
                   const std::string &messageType,
                   const Parameters &params );

private:
    QMultiHash< std::string, IMessageClient * > m_subscribers;

    QHash< std::string, IMessageClient *> m_clients;

    QReadWriteLock m_lock;
};

}
