#pragma once

#include "TemplateProcessor.h"

class QDir;

namespace Quartz {

class TemplateUtils final
{
public:
    TemplateUtils() = delete;
    ~TemplateUtils() = delete;
    TemplateUtils( const TemplateUtils & ) = delete;

    static bool generateForDir( const TemplateProcessor::Variables &variables,
                                const QDir &inDir,
                                const QDir &outDir );

private:



};


}
