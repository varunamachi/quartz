#pragma once

#include <QHash>
#include <QVariant>

#include "../utils/Macros.h"



namespace Quartz {

QZ_INTERFACE IConfigBatchLoader
{
    virtual QHash< QString, QVariant > load( const QString &path ) = 0;
}

}
