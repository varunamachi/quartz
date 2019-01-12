#pragma once

#include <memory>

#include "../QuartzCore.h"
#include "IConfigStorageStrategy.h"

namespace  Quartz {

class QUARTZ_CORE_API DefaultStorageStrategy : public IConfigStorageStrategy
{
public:
    explicit DefaultStorageStrategy(const QString &dbPath);

    ~DefaultStorageStrategy();

    bool store(const QString &domain,
                const QString &key,
                const QByteArray &value) override;

    QByteArray retrieve(const QString &domain,
                         const QString &key) const override;

    bool remove(const QString &domain,
                 const QString &key) override;

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

}
