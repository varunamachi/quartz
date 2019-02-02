#pragma once

#include <memory>

#include <QString>
#include <QVariant>

#include "../utils/Macros.h"
#include "../QuartzCore.h"

class QVariant;
class QString;

namespace Quartz {

QZ_INTERFACE IConfigStorageStrategy;
class AbstractConfigLoader;

class QUARTZ_CORE_API ConfigManager
{
public:
    explicit ConfigManager(
            std::unique_ptr<IConfigStorageStrategy> storageStragy,
            std::unique_ptr<AbstractConfigLoader> configLoader = nullptr);

    ~ConfigManager();

    void clearCache();

    void store(const QString &key,
                const QVariant &variant,
                const QString &domain = QString());

    const QVariant retrieve(const QString &key,
                             const QString &domain = "quartz") const;

    template<typename T>
    T get(const QString &key,
          const T &def = {},
          const QString &domain = "quartz") const {
        if (this->has(key, domain)) {
            return this->retrieve(key, domain).value<T>();
        }
        return def;
    }

    template<typename T>
    void set(const QString &key,
             const T &value,
             const QString &domain = "quartz") {
        this->store(key, QVariant::fromValue<T>(value), domain);
    }

    bool has(const QString &key,
              const QString &domain = "quartz") const;

    void remove(const QString &key,
                 const QString &domain = "quartz");

    void batchLoad(const QByteArray &content);

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};




}
