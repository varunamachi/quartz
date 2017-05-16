#include <QFile>
#include <QString>
#include <QStack>

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
        if( inMatch ) {
            matchCount = 0;
            auto unmatchCount = 0;
            ++ cursor;
            while( inMatch && cursor < input.size() ) {
                token = input[ cursor ];
                if( unmatchCount == 0 && token == ADV_TOKEN_END_SEC ) {
                    ++ unmatchCount;
                }
                else if( unmatchCount == 1 && token == ADV_TOKEN_FIRST ) {
                    auto block = input.mid( blockStart, cursor - 2 );
                    if( block.startsWith( ADV_IF_KW )) {
                        result = processIf( block.toString() );
                    }
                    else if( block.startsWith( ADV_FOR_KW )) {
                        result = processFor( block.toString() );
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
    return result.isEmpty() ? input.toString() : result;
}

//QString AdvancedTemplateProcessor::processForeach( const QString &input )
//{
//    //To support loop like:
//    //$[forach val in list :>
//    //  cout << val;
//    //]$

//    auto segments = input.split( ADV_FOREACH_DELEM );
//    if( segments.size() != 2 ) {
//        QZ_ERROR( "Qz:Cmn:Tmpl" ) << "Malformed foreach loop found";
//        return input;
//    }

//    auto validate = []( const QStringList &tokens ) -> bool {
//        return tokens.size() == 4
//                && tokens.at( 0 ) == ADV_FOREACH_KW
//                && tokens.at( 2 ) == ADV_FOR_IN_KW;
//    };


//    auto forTokens = segments.at( 0 ).split( QRegExp("\\s+"),
//                                             QString::SkipEmptyParts );
//    if( validate( forTokens )) {
//        QString varValue{};
//        auto varName = forTokens.at( 1 );
//        auto list = var( forTokens.at( 3 )).toStringList();
//        auto provider = [ & ]( const QString &key,
//                               const QString &def ) -> QString {
//            if( key == varName ) {
//                return varValue;
//            }
//            auto var = this->var( key );
//            if( ! var.isValid() ) {
//                return this->toString( var );
//            }
//            return def;
//        };
//        QString block;
//        QTextStream stream{ &block };
//        foreach( const QString &item, list ) {
//            varValue = item;
//            TemplateProcessor::process( input, stream, provider );
//        }
//        return  block;
//    }
//    else {
//        //print errore
//    }
//    return input;
//}

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
    if( ch == ' '
            || ch == '\t'
            || ch == '\n'
            || ch == '\r' ) {
        ++ cursor;
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
    while( cursor <= input.size() ) {
        if( cursor == input.size()
                || checkWhitespace( input, cursor )
                || check( input, ":>", cursor )) {
            auto num = cursor - tokenStart - 1;
            if( num != 0 ) {
                auto token = input.mid( tokenStart, num );
                if( tokenNumber == 0 && token == ADV_FOR_KW ) {
                    //expected
                    continue;
                }
                else if( tokenNumber == 1 ) {
                    varName = token;
                }
                else if( tokenNumber == 2 && token == ADV_FOR_IN_KW ) {
                    //expected
                    continue;
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
                    //We got the content, we are done with the looping
                    content = token;
                    break;
                }
            }
            tokenStart = -1;
        }
        else {
            if( tokenStart == -1 ) {
                tokenStart = cursor;
            }
            ++ cursor;
        }
    }
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
                TemplateProcessor::process( input, stream, provider );
                stream << '\n';
            }
        }
        else {
            auto list = var( listName ).toStringList();
            foreach( const QString &item, list ) {
                value = item;
                TemplateProcessor::process( input, stream, provider );
                stream << '\n';
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
