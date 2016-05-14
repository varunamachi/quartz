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
    void subscribe( const QString &messageType,
                    IMessageClient *sub );

    void subscribe( const QStringList &messageTypes,
                    IMessageClient *sub );

    void removeSubscriber( IMessageClient *client );

    void removeSubscriber( const QString &clientId );

    void notify( const IMessageClient *originator,
                 const QString &messageType,
                 const Parameters &params );

signals:
    void onNotify( const IMessageClient *originator,
                   const QString &messageType,
                   const Parameters &params );

private:
    QMultiHash< QString, IMessageClient * > m_subscribers;

    QHash< QString, IMessageClient *> m_clients;

    QReadWriteLock m_lock;
};

}
