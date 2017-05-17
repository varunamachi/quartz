#include <QFile>
#include <QString>
#include <QStack>
#include <QDebug>

#include <core/logger/Logging.h>

#include "AdvancedTemplateProcessor.h"

namespace Quartz {

const QString ADV_TOKEN_FIRST = QString{ "$" };
const QString ADV_TOKEN_BEGIN_SEC = QString{ "[" };
const QString ADV_TOKEN_END_SEC = QString{ "]" };
const QString ADV_FOREACH_DELEM = QString{ ":>" };
const QString ADV_FOR_KW = QString{ "FOR" };
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
        auto blockExpanded = processBlocks( input );
        result = TemplateProcessor::process( blockExpanded, output );
    }
    else {
        QZ_ERROR( "Qz:Cmn:Tmpl" ) << "Invalid template text given";
    }

    return result;
}

QString AdvancedTemplateProcessor::processBlocks( const QString &input ) {
    auto cursor = 0;
    auto matchCount = 0;
    auto inMatch = false;
    auto blockStart = -1;
    QString result{};
    QTextStream  stream{ &result };
    while( cursor < input.size() ) {
        auto token = input[ cursor ];
        if( matchCount == 0 && token == ADV_TOKEN_FIRST ) {
            ++ matchCount;
        }
        else if( matchCount == 1 && token == ADV_TOKEN_BEGIN_SEC ) {
            ++ matchCount;
            blockStart = cursor + 1;
            if( inMatch ) {
                auto block = processBlocks( input.right( cursor ));
                stream << block;
            }
            inMatch = true;
        }
        else {
            if( matchCount == 1 ) {
                //because I ate the first token in the first if
                stream << ADV_TOKEN_FIRST;
                matchCount = 0;
            }
            stream << token;
        }
        ++ cursor;

        if( inMatch ) {
            matchCount = 0;
            auto unmatchCount = 0;
            while( inMatch && cursor < input.size() ) {
                token = input[ cursor ];
                qDebug() << "UM: " << token;
                if( unmatchCount == 0 && token == ADV_TOKEN_END_SEC ) {
                    qDebug() << "One";
                    ++ unmatchCount;
                }
                else if( unmatchCount == 1 && token == ADV_TOKEN_FIRST ) {
                    qDebug() << "Two";
                    auto block = input.mid( blockStart,
                                            cursor - blockStart - 2 );
                    qDebug() << "BLOCK: " << block;
                    if( block.startsWith( ADV_IF_KW )) {
                        auto content = processIf( block );
                        stream << content;
                    }
                    else if( block.startsWith( ADV_FOR_KW )) {
                        auto content = processFor( block );
                        stream << content;
                    }
                    else {
                        stream << block;
                    }
                    inMatch = false;
                    -- unmatchCount;
                }
                ++ cursor;
            }
        }


    }
    return result.isEmpty() ? input : result;
}

static bool check( const QString &input,
                   const QString &token,
                   QZ_IN_OUT int &cursor )
{
    bool result = true;
    auto dupCursor = cursor;
    for( auto i = 0; i < token.size(); ++ i, ++ dupCursor ) {
        if( dupCursor >= input.size()
                || input[ dupCursor ] != token[ i ]) {
            result = false;
            break;
        }
    }
    if( result ) {
        cursor = cursor + token.size();
    }
    return result;
}

static inline bool checkWhitespace( const QString &input,
                                    QZ_IN_OUT int &cursor )
{
    auto result = false;
    auto ch = input.at( cursor );
    while( cursor < input.size()
           && ( ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' )) {
        ++ cursor;
        ch = input.at( cursor );
        result = true;
    }
    return result;
}

struct Range
{
    Range( int start, int end, int increment )
        : m_start{ start }
        , m_end{ end }
        , m_inc{ increment }
    {
        m_valid = ( m_start != m_end )
                && (( m_start < m_end  &&  m_inc > 0 )
                || ( m_start > m_end  &&  m_inc < 0 ));
    }

    Range()
        : m_start{ 0 }
        , m_end{ 0 }
        , m_inc{ 0 }
        , m_valid{ false }
    {

    }


    int m_start;

    int m_end;

    int m_inc;

    bool m_valid;
};

Range parseRange( const QString &range )
{
    auto rg = range.mid( 4, ( range.size() - 2 - 4 ));
    auto parts = rg.split( "," );
    Range result{};
    if( parts.size() == 2 || parts.size() == 3 ) {
        auto startOk = true;
        auto endOk = true;
        auto incOk = true;
        auto start = parts.at( 0 ).trimmed().toInt( &startOk );
        auto end = parts.at( 1 ).trimmed().toInt( &endOk );
        auto inc = 1;
        if( parts.size() > 2 ) {
            inc = parts.at( 2 ).trimmed().toInt( &incOk );
        }
        if( startOk && endOk && incOk ) {
            result = Range{ start, end, inc };
        }
    }
    return result;
}

QString AdvancedTemplateProcessor::processFor( const QString &input )
{
    //For parsing for-each and for-range loop and expanding the content
    auto cursor = 0;
    auto tokenStart = -1;
    auto tokenNumber = 0;
    QString content;
    QString varName;
    QString listName;
    Range range;
    qDebug() << "INPUT: " << input;
    while( cursor <= input.size() ) {
        if( cursor == input.size() || checkWhitespace( input, cursor )) {
            auto num = cursor - tokenStart - 1;
            if( num > 0 ) {
                auto token = input.mid( tokenStart, num );
                qDebug() << "TOKEN: " << token << " -- " << tokenStart;
                if( tokenNumber == 0 && token != ADV_FOR_KW ) {
                    QZ_ERROR( "Qz:Cmn:Tmpl" )
                            << "Could not find FOR keyword in for loop";
                    break;
                }
                else if( tokenNumber == 1 ) {
                    varName = token;
                }
                else if( tokenNumber == 2 && token != ADV_FOR_IN_KW ) {
                    QZ_ERROR( "Qz:Cmn:Tmpl" )
                            << "Could not find IN keyword in for loop";
                    break;
                }
                else if( tokenNumber == 3 ) {
                    auto list = token;
                    if( list.startsWith( "range" )) {
                        range = parseRange( list );
                        if( ! range.m_valid ) {
                            QZ_ERROR( "Qz:Cmn:Tmpl" )
                                    << "Failed to parse range of for loop";
                            break;
                        }
                    }
                    else {
                        listName = token;
                    }
                }
                else if( tokenNumber == 4 ) {
//                    QZ_ERROR( "Qz:Cmn:Tmpl" )
                    qDebug() << "We shouldnt come here!!!" << token;
                }
                ++ tokenNumber;
            }
            tokenStart = -1;
            if( cursor == input.size() ) {
                break;
            }
        }
        else if( check( input, ":>", cursor )){
            content = input.mid( cursor, input.size() - cursor - 1 );
            break;
        }
        else {
            if( tokenStart == -1 ) {
                tokenStart = cursor;
            }
            ++ cursor;
        }
    }

    qDebug() << "VarName :" << varName
             << "\nListName: " << listName
             << "\nContent: "  << content;


    //Now expand the content if its not empty
    if( ! content.isEmpty() ) {
        QString value = "";
        auto provider = [ & ]( const QString &key,
                               const QString &def ) -> QString {
            if( key == varName ) {
                return value;
            }
            auto var = this->var( key );
            if( ! var.isValid() ) {
                return this->toString( var );
            }
            return def;
        };
        QString output;
        QTextStream stream{ &output };
        if( range.m_valid ) {
            for( auto i = range.m_start; i < range.m_end; i += range.m_inc ) {
                value = QString::number( i );
                TemplateProcessor::process( content, stream, provider );
            }
        }
        else {
            auto list = var( listName ).toStringList();
            foreach( const QString &item, list ) {
                value = item;
                TemplateProcessor::process( content, stream, provider );
            }
        }
        return output;
    }
    QZ_ERROR( "Qz:Cmn:Tmpl" ) << "Failed to parse for loop";
    return QString{};
}

QString AdvancedTemplateProcessor::processIf( const QString &/*input*/ )
{
    //TO support conditions like
    //$[if var == "0"]$
    return QString{}; //not supported yet
}

}
