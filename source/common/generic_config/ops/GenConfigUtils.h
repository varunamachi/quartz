#pragma once

#include <QVariantMap>

#include "../../QuartzCommon.h"

namespace Quartz {

class Config;

class QUARTZ_COMMON_API GenConfigUtils
{
public:
    GenConfigUtils() = delete;

    static void updateModel(const QVariantHash &values, Config *config);

};

}
