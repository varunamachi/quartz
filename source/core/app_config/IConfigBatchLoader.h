#pragma once

#include <functional>

#include <QHash>
#include <QVariant>

#include "../utils/Macros.h"



namespace Quartz {

QZ_INTERFACE IConfigBatchLoader
{
    using StoreFunc = std::function< void( const QString &,
                                           const QString &,
                                           const QVariant & )>;

    virtual void load( StoreFunc storeFunc ) = 0;

    virtual ~IConfigBatchLoader() { }
};

}
