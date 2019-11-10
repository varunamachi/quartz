#pragma once

#include <memory>

#include "../QuartzCore.h"
#include "AbstractConfigLoader.h"

namespace Quartz {

class QUARTZ_CORE_API XMLConfigLoader : public AbstractConfigLoader {
public:
    explicit XMLConfigLoader(StoreFunc storeFunc);

    ~XMLConfigLoader();

    bool load(const QByteArray content) const override;
};

} // namespace Quartz
