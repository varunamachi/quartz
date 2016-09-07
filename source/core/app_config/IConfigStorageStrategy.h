#pragma once

#include <QHash>

class QVariant;

#include "../utils/Macros.h"

namespace Quartz {

QZ_INTERFACE IConfigStorageStrategy
{
    virtual void store( const QString &key, const QVariant &value ) = 0;

    virtual QVariant retrieve( const QString &key ) const = 0;

    virtual bool has( const QString &key ) const = 0;

    virtual bool load( const QHash< QString, QVariant > &values ) = 0;
};


}
