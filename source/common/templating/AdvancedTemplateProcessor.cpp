#include <QFile>
#include <QString>
#include <QStack>

#include <core/logger/Logging.h>

#include "AdvancedTemplateProcessor.h"

namespace Quartz {

const QString ADV_TOKEN_FIRST = QString{ "$" };
const QString ADV_TOKEN_SEC = QString{ "[" };
const QString ADV_FOREACH_DELEM = QString{ ":>" };
const QString ADV_FOREACH_KW = QString{ "FOREACH" };
const QString ADV_FOR_KW = QString{ "FOREACH" };
const QString ADV_IF_KW = QString{ "IF" };
const QString ADV_FOR_IN_KW = QString{ "IN" };


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
    if( ! input.isEmpty() ) {
        auto blockExpanded = processBlocks( QStringRef{ &input });
        result = TemplateProcessor::process( blockExpanded, output );
    }
    else {
        QZ_ERROR( "Qz:Cmn:Tmpl" ) << "Invalid template text given";
    }

    return result;
}

QString AdvancedTemplateProcessor::processBlocks( const QStringRef &input ) {
    auto cursor = 0;
    auto matchCount = 0;
    auto inMatch = false;
    auto blockStart = -1;
    QString result;
    QTextStream  stream{ &result };
    while( cursor < input.size() ) {
        auto token = input[ cursor ];
        if( matchCount == 0 && token == ADV_TOKEN_FIRST ) {
            ++ matchCount;
        }
        else if( matchCount == 1 && token == ADV_TOKEN_SEC ) {
            ++ matchCount;
            blockStart = cursor + 1;
            if( inMatch ) {
                auto block = processBlocks( input.right( cursor ));
                stream << block;
            }
        }
        else {
            if( matchCount == 1 ) {
                //because I ate the first token in the first if
                stream << ADV_TOKEN_FIRST;
                matchCount = 0;
            }
            stream << token;
        }
        if( inMatch ) {
            matchCount = 0;
            auto unmatchCount = 0;
            ++ cursor;
            while( inMatch && cursor < input.size() ) {
                token = input[ cursor ];
                if( unmatchCount == 0 && token == ADV_TOKEN_SEC ) {
                    ++ unmatchCount;
                }
                else if( unmatchCount == 1 && token == ADV_TOKEN_FIRST ) {
                    auto block = input.mid( blockStart, cursor - 2 );
                    if( block.startsWith( ADV_FOREACH_KW )) {
                        result = processForeach( *block.string() );
                    }
                    else if( block.startsWith( ADV_IF_KW )) {
                        result = processIf( *block.string() );
                    }
                    else if( block.startsWith( ADV_FOR_KW )) {
                        result = processFor( *block.string() );
                    }
                    inMatch = false;
                    ++ cursor;
                    -- unmatchCount;
                    break;
                }
                ++ cursor;
            }
        }
        else {
            ++ cursor;
        }
    }
    return result;
}

QString AdvancedTemplateProcessor::processForeach( const QString &input )
{
    //To support loop like:
    //$[forach val in list :>
    //  cout << val;
    //]$

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
        QTextStream stream{ &block };
        foreach( const QString &item, list ) {
            varValue = item;
            TemplateProcessor::process( input, stream, provider );
        }
        return  block;
    }
    else {
        //print errore
    }
    return input;
}

QString AdvancedTemplateProcessor::processFor( const QString &/*input*/ )
{
    //To support loops like:
    //$[for i in range(1, 100)]$
    //Not implemented yet
    return QString{};
}

QString AdvancedTemplateProcessor::processIf( const QString &/*input*/ )
{
    //TO support conditions like
    //$[if var == "0"]$
    return QString{}; //not supported yet
}

}
