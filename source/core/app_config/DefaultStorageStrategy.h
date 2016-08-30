#pragma once

#include <memory>

#include "IConfigStorageStrategy.h"

namespace  Quartz {

class DefaultStorageStrategy : public IConfigStorageStorage
{
public:
    void store( const QString &key, const QVariant &value );

    QVariant retrieve( const QString &key ) const;

    bool has( const QString &key ) const;

    bool load( const QHash<QString, QVariant> &values );

private:
    class Data;
    std::unique_ptr< Data > m_data;
};

}
