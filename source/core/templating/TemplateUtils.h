#pragma once

#include <functional>

#include "TemplateProcessor.h"
#include "../utils/Macros.h"


class QDir;

namespace Quartz {


class QUARTZ_CORE_API TemplateUtils final
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

private:



};


}
