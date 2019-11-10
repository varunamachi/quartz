
#include <core/app_config/ConfigManager.h>

#include <common/generic_config/model/Config.h>
#include <common/generic_config/model/Param.h>

#include "GenConfigUtils.h"

namespace Quartz {

void GenConfigUtils::updateModel(const QVariantHash& values, Config* config) {
    for (auto it = values.begin(); it != values.end(); ++it) {
        auto param = config->param(it.key());
        if (param != nullptr) {
            param->setValue(it.value());
        }
    }
}

} // namespace Quartz
