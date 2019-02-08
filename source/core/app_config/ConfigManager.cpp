#include <QVariant>
#include <QDataStream>

#include "../logger/Logging.h"
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

    using Cache = QHash< QString, QVariantHash>;

    std::unique_ptr<IConfigStorageStrategy> m_storage;

    std::unique_ptr<AbstractConfigLoader> m_configLoader;

    mutable Cache m_cache;
};

const QVariant dummy;


ConfigManager::ConfigManager(
        std::unique_ptr<IConfigStorageStrategy> storageStragy,
        std::unique_ptr<AbstractConfigLoader> configLoader)
    : m_impl(std::make_unique<Impl>( std::move(storageStragy),
                                     std::move(configLoader)))
{
}


ConfigManager::~ConfigManager()
{

}

const QVariant ConfigManager::retrieve(const QString &key,
                                       const QString &domain) const
{
    auto var = m_impl->cachedValue(domain, key);
    if (var.isValid()) {
        return var;
    }
    else {
        auto raw = m_impl->m_storage->retrieve(domain, key);
        if (! (raw.isNull() || raw.isEmpty())) {
            QDataStream stream(raw);
            stream.setVersion(QDataStream::Qt_5_2);
            QVariant val;
            stream >> val;
            if (val.isValid()) {
                m_impl->insertToCache(domain, key, val);
                return val;
            }
        }
    }
    return QVariant{};
}

void  ConfigManager::store(
             const QString &key,
             const QVariant &value,
             const QString &domain)
{
    QByteArray raw;
    QDataStream stream{&raw, QIODevice::WriteOnly};
    stream.setVersion(QDataStream::Qt_5_2);
    stream << value;
    if (m_impl->m_storage->store(domain, key, raw)) {
        m_impl->insertToCache(domain, key, value);
    }
    emit configChanged(key, value, domain);
}

bool ConfigManager::has(const QString &key, const QString &domain) const
{
    bool has = m_impl->cacheContains(domain, key);
    if (! has) {
        auto var = retrieve(key, domain);
        has = var.isValid();
    }
    return has;
}

void ConfigManager::remove(const QString &key, const QString &domain)
{
    if (m_impl->m_storage->remove(domain, key)) {
        m_impl->m_cache[ domain ].remove(key);
    }
    emit configRemoved(key, domain);
}

void ConfigManager::clearCache()
{
    m_impl->m_cache.clear();
}

void  ConfigManager::batchLoad(const QByteArray &content)
{
    if (m_impl->m_configLoader != nullptr) {
        m_impl->m_configLoader->load(content);
    }
}

QVariantHash ConfigManager::allFromDomain(const QString &domain) const
{
    auto decoder = [](const QByteArray &raw) -> QVariant {
        QDataStream stream(raw);
        stream.setVersion(QDataStream::Qt_5_2);
        QVariant val;
        stream >> val;
        //print error if any?
        return val;
    };
    auto values = m_impl->m_storage->allFromDomain(domain, decoder);
    return values;
}


}
