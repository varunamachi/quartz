#pragma once

#include <memory>

#include "../utils/Macros.h"

class QVariant;
class QString;

namespace Quartz {

QZ_INTERFACE IConfigStorageStrategy;

class ConfigManager
{
public:
    explicit ConfigManager(
            std::unique_ptr< IConfigStorageStrategy > storageStragy );

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
