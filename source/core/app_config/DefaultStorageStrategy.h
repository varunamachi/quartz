#pragma once

#include <memory>
#include <functional>

#include <QVariantHash>

#include "../QuartzCore.h"
#include "IConfigStorageStrategy.h"

namespace  Quartz {


class QUARTZ_CORE_API DefaultStorageStrategy : public IConfigStorageStrategy
{
public:


    explicit DefaultStorageStrategy(const QString &dbPath);

    ~DefaultStorageStrategy() override;

    bool store(const QString &domain,
                const QString &key,
                const QByteArray &value) override;

    QByteArray retrieve(const QString &domain,
                         const QString &key) const override;

    bool remove(const QString &domain,
                 const QString &key) override;

    QVariantHash allFromDomain(const QString &domain,
                               BlobDecoder decoder) const override;

private:
    class Data;
    std::unique_ptr<Data> m_data;
};

}
