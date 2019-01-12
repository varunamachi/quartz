#include <QVariant>
#include <QDataStream>

#include "IConfigStorageStrategy.h"
#include "AbstractConfigLoader.h"
#include "ConfigManager.h"

namespace Quartz {

class ConfigManager::Impl
{
public:
    explicit Impl(std::unique_ptr<IConfigStorageStrategy> storage,
                   std::unique_ptr<AbstractConfigLoader> configLoader)
        : m_storage(std::move(storage))
        , m_configLoader(std::move(configLoader))
    {

    }

    AbstractConfigLoader * configLoader()
    {
        return m_configLoader.get();
    }

    const QVariant retrieve(const QString &domain,
                             const QString &key) const
    {
        auto var = cachedValue(domain, key);
        if (var.isValid()) {
            return var;
        }
        else {
            auto raw = m_storage->retrieve(domain, key);
            if (! (raw.isNull() || raw.isEmpty())) {
                QDataStream stream(raw);
                stream.setVersion(QDataStream::Qt_5_2);
                QVariant val;
                stream >> val;
                if (val.isValid()) {
                    insertToCache(domain, key, val);
                    return val;
                }
            }
        }
        return QVariant{};
    }

    void  store(const QString &domain,
                 const QString &key,
                 const QVariant &value)
    {
        QByteArray raw{};
        QDataStream stream{ &raw, QIODevice::WriteOnly };
        stream.setVersion(QDataStream::Qt_5_2);
        stream << value;
        if (m_storage->store(domain, key, raw)) {
            insertToCache(domain, key, value);
        }
    }

    bool has(const QString &domain,
              const QString &key) const
    {
        bool has = cacheContains(domain, key);
        if (! has) {
            auto var = retrieve(domain, key);
            has = var.isValid();
        }
        return has;
    }

    void remove(const QString &domain, const QString &key)
    {
        if (m_storage->remove(domain, key)) {
            m_cache[ domain ].remove(key);
        }
    }

    void clearCache()
    {
        m_cache.clear();
    }



private:
    bool cacheContains(const QString &domain, const QString key) const
    {
        bool result = m_cache.contains(domain)
                && m_cache.value(domain).contains(key);
        return result;
    }

    QVariant cachedValue(const QString &domain, const QString &key) const
    {
        QVariant var = m_cache.value(domain).value(key);
        return var;
    }

    void insertToCache(const QString &domain,
                        const QString &key,
                        const QVariant &value) const
    {
        if (! m_cache.contains(domain)) {
            QHash< QString, QVariant > subCache;
            subCache.insert(key, value);
            m_cache.insert(domain, subCache);
        }
        else {
            m_cache[ domain ][ key ] = value;
        }
    }

    using Cache = QHash< QString,
                         QHash< QString, QVariant >>;

    std::unique_ptr<IConfigStorageStrategy> m_storage;

    std::unique_ptr<AbstractConfigLoader> m_configLoader;

    mutable Cache m_cache;
};

const QVariant dummy;


ConfigManager::ConfigManager(
        std::unique_ptr<IConfigStorageStrategy> storageStragy,
        std::unique_ptr<AbstractConfigLoader> configLoader)
//    : m_data(std::make_unique<ConfigManager::Data>(
//                  std::move(storageStragy),
//                  std::move(configLoader))
    : m_impl(new ConfigManager::Impl(
                  std::move(storageStragy),
                  std::move(configLoader)))

{
}


ConfigManager::~ConfigManager()
{

}


void  ConfigManager::clearCache()
{
    m_impl->clearCache();
}


void  ConfigManager::store(const QString &key,
                            const QVariant &variant,
                            const QString &domain)
{
    return m_impl->store(domain, key, variant);
}

const QVariant ConfigManager::retrieve(const QString &key,
                                        const QString &domain) const
{
    return m_impl->retrieve(domain, key);
}


bool  ConfigManager::has(const QString &key, const QString &domain) const
{
    return m_impl->has(domain, key);
}


void ConfigManager::remove(const QString &key, const QString &domain)
{
    m_impl->remove(domain, key);
}


void  ConfigManager::batchLoad(const QByteArray &content)
{
    if (m_impl->configLoader() != nullptr) {
        m_impl->configLoader()->load(content);
    }
}



}
