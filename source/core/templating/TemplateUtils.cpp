
#include <QDir>
#include <QStringList>
#include <QString>

#include "../logger/Logging.h"
#include "TemplateUtils.h"

namespace Quartz {

bool TemplateUtils::generateForDir(
        const TemplateProcessor::Variables &variables,
        const QDir &inDir,
        const QDir &outDir )
{
    TemplateProcessor processor{ variables };
    bool result = true;
    QStringList names;
    names << ".template";
    auto list = inDir.entryInfoList( names );
    for( int i = 0; i < list.size(); ++ i ) {
        auto entry = list.at( i );
        auto inputPath = entry.absoluteFilePath();
        auto outputPath = outDir.absoluteFilePath( entry.completeBaseName() );
        auto res = processor.process( inputPath, outputPath );
        if( ! res ) {
            QZ_ERROR( "Qz:Core" )
                    << "Failed to process template file at " << inputPath;
        }
        result = result && res;
    }
    return result;
}





}
