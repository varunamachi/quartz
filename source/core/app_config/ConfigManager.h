#pragma once

#include <memory>

#include "IConfigStorageStrategy.h"

namespace Quartz {



class ConfigManager
{
public:
    explicit ConfigManager( IConfigStorageStorage *storageStragy );

    ~ConfigManager();

    void clearCache();

    void store( const QString &key, const QVariant &variant );

    const QVariant & retrieve( const QString &key );

    bool has( const QString &key );

    void loadFromFile( const QString &path );

private:
    class Data;
    std::unique_ptr< Data > m_data;
};




}
