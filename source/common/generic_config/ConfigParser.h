#pragma once

#include <QString>
#include <QHash>

#include <core/utils/Macros.h>
#include <core/QuartzCore.h>


#include "Param.h"
#include "Config.h"

namespace Quartz {

class ConfigParser
{
public:
    std::size_t parse( const QString &filePath,
                       QZ_OUT QHash< QString, Config::Ptr > &configsOut);

private:

};


}
