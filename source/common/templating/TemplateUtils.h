#pragma once

#include <functional>
#include <core/utils/Macros.h>

#include "../QuartzCommon.h"
#include "TemplateProcessor.h"


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

    static bool generateForDir( const TemplateProcessor::Variables &variables,
                                const QDir &inDir,
                                const QDir &outDir,
                                FileNameSubstituter substr = nullptr );

    static QVector< std::shared_ptr< Template >> templatesInDir( QDir dir );

private:



};


}
