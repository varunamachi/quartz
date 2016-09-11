#pragma once

#include <QHash>


class QVariant;

#include "../utils/Macros.h"

namespace Quartz {

QZ_INTERFACE IConfigStorageStrategy
{
    virtual bool store( const QString &domain,
                        const QString &key,
                        const QByteArray &data ) = 0;

    virtual QByteArray retrieve(
                const QString &domain,
                const QString &key ) const = 0;

    virtual bool remove( const QString &domain,
                         const QString &key ) = 0;

    virtual ~IConfigStorageStrategy() { }
};


}
