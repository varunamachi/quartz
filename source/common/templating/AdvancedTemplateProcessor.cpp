#include <QFile>

#include <core/logger/Logging.h>

#include "AdvancedTemplateProcessor.h"

namespace Quartz {

const QString ADV_END_TOKEN = QString{ "%>" };
const QString ADV_START_TOKEN = QString{ "<%" };
const QString ADV_FOREACH_DELEM = QString{ ":>" };
const QString ADV_FOREACH_KW = QString{ "foreach" };
const QString ADV_FOR_IN_KW = QString{ "in" };


struct AdvancedTemplateProcessor::Data
{
    explicit Data()
    {

    }

};

AdvancedTemplateProcessor::AdvancedTemplateProcessor(
        const TemplateProcessor::Variables &vars )
    : TemplateProcessor{ vars }
    , m_data{ new Data{}}
{

}

AdvancedTemplateProcessor::~AdvancedTemplateProcessor()
{
}


bool AdvancedTemplateProcessor::process( QString &input,
                                         QTextStream &output )
{
    bool result = false;
    auto firstBlocks = input.split( ADV_END_TOKEN );
    foreach( QString one, firstBlocks ) {
        if( one.contains( ADV_START_TOKEN )) {
            auto loopBlock = one.split( ADV_START_TOKEN );
            if( loopBlock.size() == 2 ) {
                //now parse the for loop
                //if could be tricky since we need to evaluate the condition
                //Also if we are using parent's process function to replace
                //  variables then we need a way to temporarily add variables
                //  to variable map so that loop variables get replaced
            }
            else {
                //template is wrong
            }
        }
    }

    return result;
}

QString AdvancedTemplateProcessor::processForeach( QString &input )
{
    auto segments = input.split( ADV_FOREACH_DELEM );
    if( segments.size() != 2 ) {
        QZ_ERROR( "Qz:Cmn:Tmpl" ) << "Malformed foreach loop found";
        return input;
    }

    auto validate = []( const QStringList &tokens ) -> bool {
        return tokens.size() == 4
                && tokens.at( 0 ) == ADV_FOREACH_KW
                && tokens.at( 2 ) == ADV_FOR_IN_KW;
    };


    auto forTokens = segments.at( 0 ).split( QRegExp("\\s+"),
                                             QString::SkipEmptyParts );
    if( validate( forTokens )) {
        QString varValue{};
        auto varName = forTokens.at( 1 );
        auto list = var( forTokens.at( 3 )).toStringList();
        auto provider = [ & ]( const QString &key,
                               const QString &def ) -> QString {
            if( key == varName ) {
                return varValue;
            }
            auto var = this->var( key );
            if( ! var.isValid() ) {
                return this->toString( var );
            }
            return def;
        };
        QString block;
        QTextString stream{ &block };
        foreach( const QString &item, list ) {
            varValue = item;
            process( input, stream, provider );
        }
        return  block;
    }
    else {
        //print error
    }
    return input;
}

}
