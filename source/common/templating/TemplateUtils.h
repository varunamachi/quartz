#pragma once

#include <functional>
#include <memory>

#include <core/utils/Macros.h>

#include "../QuartzCommon.h"


class QDir;

namespace Quartz {

class Template;


class QUARTZ_COMMON_API TemplateUtils final
{
public:
    using FileNameSubstituter = std::function< QString( const QString & )>;

    TemplateUtils() = delete;
    ~TemplateUtils() = delete;
    TemplateUtils( const TemplateUtils & ) = delete;

    static QVector< std::shared_ptr< Template >> templatesInDir( QDir dir );

private:



};


}
