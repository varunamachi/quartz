
#include <QDir>
#include <QStringList>
#include <QString>

#include <core/logger/Logging.h>

#include "AdvancedTemplateProcessor.h"
#include "Template.h"
#include "TemplateUtils.h"
#include "TemplateContainerParser.h"


namespace Quartz {

bool TemplateUtils::generateForDir(
        const TemplateProcessor::Variables &variables,
        const QDir &inDir,
        const QDir &outDir,
        FileNameSubstituter substr )
{
    AdvancedTemplateProcessor processor{ variables };
    bool result = true;
    QStringList names;
//    names << ".template";
    auto list = inDir.entryInfoList( names );
    for( int i = 0; i < list.size(); ++ i ) {
        auto entry = list.at( i );
        if( entry.suffix() == "template" ) {
            auto inputPath = entry.absoluteFilePath();
            auto outFileName = entry.completeBaseName();
            if( substr != nullptr ) {
                auto substitute = substr( entry.fileName() );
                if( ! substitute.isEmpty() ) {
                    outFileName = substitute;
                }
            }
            auto outputPath = outDir.absoluteFilePath( outFileName );
//            auto tp = static_cast< TemplateProcessor *>( &processor );
            auto res = processor.process( inputPath, outputPath );
            if( ! res ) {
                QZ_ERROR( "Qz:Core" )
                        << "Failed to process template file at " << inputPath;
            }
            result = result && res;
        }
    }
    return result;
}

QVector< std::shared_ptr< Template >> TemplateUtils::templatesInDir( QDir dir )
{
    QVector< std::shared_ptr< Template >> templates;
    auto list = dir.entryInfoList();
    for( int i = 0; i < list.size(); ++ i ) {
        auto entry = list.at( i );
        if( entry.suffix() == "xml" ) {
            auto inputPath = entry.absoluteFilePath();
            //read the file
            //parse it using continer parser
            //add the resulting vector to result vector
            //ignore errors... because we might try to parse non container xml
            //    -> which is fine

        }
    }
    return templates;
}





}
