#include <QVariant>

#include "DefaultStorageStrategy.h"

namespace Quartz {




void DefaultStorageStrategy::store( const QString &key,
                                    const QVariant &value )
{

}


QVariant DefaultStorageStrategy::retrieve( const QString &key ) const
{
    return QVariant{ };
}


bool DefaultStorageStrategy::has( const QString &key ) const
{
    return false;
}


bool DefaultStorageStrategy::load( const QHash<QString, QVariant> &values )
{
    return false;
}


}
