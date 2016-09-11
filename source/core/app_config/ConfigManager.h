#pragma once

#include <memory>

#include <QString>

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

    void store( const QString &key,
                const QVariant &variant,
                const QString &domain = QString{ } );

    const QVariant retrieve( const QString &key,
                             const QString &domain = QString{} ) const;

    bool has( const QString &key,
              const QString &domain = QString{} ) const;

    void remove( const QString &key,
                 const QString &domain = QString{} );

    void loadFromFile( const QString &path );

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;
};




}
