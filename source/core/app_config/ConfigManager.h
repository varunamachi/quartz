#pragma once

#include <memory>

#include <QString>
#include <QVariant>
#include <QObject>

#include "../utils/Macros.h"
#include "../QuartzCore.h"

class QVariant;
class QString;

namespace Quartz {

//struct AbstractConfigChangeListener
//{
//    virtual const QString & domain() const = 0;

//    virtual void onConfigChange(const QString &key, const QVariant &value) = 0;

//    virtual ~AbstractConfigChangeListener() {}

//    AbstractConfigChangeListener();
//};


QZ_INTERFACE IConfigStorageStrategy;
class AbstractConfigLoader;

class QUARTZ_CORE_API ConfigManager : public QObject
{
    Q_OBJECT

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

Q_SIGNALS:
    void configChanged(const QString &key,
                       const QVariant &val,
                       const QString &domain);

    void configRemoved(const QString &key,
                       const QString &domain);

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};




}
