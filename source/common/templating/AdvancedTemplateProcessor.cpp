#include <QFile>
#include <QString>
#include <QStack>
//#include <QDebug>

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
    explicit Data( const TemplateProcessor::Variables &vars )
        : m_variables{ vars }
        , m_lastError{ "" }
    {

    }

    TemplateProcessor::Variables m_variables;

    QString m_lastError;

};

AdvancedTemplateProcessor::AdvancedTemplateProcessor(
        const TemplateProcessor::Variables &vars )
    : m_data{ new Data{ vars }}
{

}

AdvancedTemplateProcessor::~AdvancedTemplateProcessor()
{
}

bool AdvancedTemplateProcessor::replaceVariables(
        const QString &input,
        QTextStream &output,
        ValueProvider getVar )
{
        bool result = true;
        auto cursor = 0;
        auto matchCount = 0;
        auto inMatch = false;
        while( cursor < input.size() ) {
            auto token = input[ cursor ];
            if( matchCount == 0 && token == '$' ) {
                ++ matchCount;
            }
            else if( matchCount == 1 && token == '<' ) {
                ++ matchCount;
                inMatch = true;
            }
            else {
                if( matchCount == 1 ) {
                    //because I ate the doller in the first if
                    output << '$';
                    matchCount = 0;
                }
                output << token;
            }
            if( inMatch ) {
                matchCount = 0;
                auto unmatchCount = 0;
                QString key;
                QTextStream stream{ &key };
                //We copy the cursor because the replaced value can also be a
                //placeholder and original cursor is still at the beginning of
                //the replaced placeholder
    //            auto matchCursor = cursor + 1;
                ++ cursor;
                while( inMatch && cursor < input.size() ) {
                    token = input[ cursor ];
                    if( unmatchCount == 0 && token == '>' ) {
                        ++ unmatchCount;
                    }
                    else if( unmatchCount == 1 && token == '$' ) {
                        stream.flush();
                        auto def = "$<" + key + ">$";
                        output << getVar( key, def );
                        inMatch = false;
                        -- unmatchCount;
                        ++ cursor;
                        break;
                    }
                    else {
                        if( unmatchCount == 1 ) {
                            stream << '$';
                            unmatchCount = 0;
                        }
                        stream << token;
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


bool AdvancedTemplateProcessor::process( QString &input,
                                         QTextStream &output )
{
    bool result = false;
    if( ! input.isEmpty() ) {
        auto blockExpanded = processBlocks( input );
        result = replaceVariables(
                    blockExpanded,
                    output,
                    [ & ]( const QString &key, const QString &def ) -> QString {
            auto var = m_data->m_variables.value( key, def );
            return this->toString( var );
        } );
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
                if( unmatchCount == 0 && token == ADV_TOKEN_END_SEC ) {
                    ++ unmatchCount;
                }
                else if( unmatchCount == 1 && token == ADV_TOKEN_FIRST ) {
                    auto block = input.mid( blockStart,
                                            cursor - blockStart - 2 );
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



Range parseRange( const QString &input,
                  QZ_IN_OUT int &cursor )
{
    auto start = input.indexOf( '(' ) + 1;
    auto size = input.indexOf( ')' ) - start;
    auto block = input.mid( start, size );
//    auto rg = rangeParam.mid( 1, ( rangeParam.size() - 2 - 1 ));
    auto parts = block.split( "," );
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
    if( result.m_valid ) {
        cursor = cursor + size + 6 + 1;
    }
    return result;
}

bool AdvancedTemplateProcessor::process( const QString &inputPath,
                                         const QString &outputPath )
{
    QFile inputFile{ inputPath };
    if( ! inputFile.open( QFile::ReadOnly )) {
        QZ_ERROR( "Qz:Cmn:Tmpl" ) << "Failed to open template file at "
                                  << inputPath;
        m_data->m_lastError = QObject::tr( "Could not open template input "
                                           "file at %1" ).arg( inputPath);
        return false;
    }
    QFile outputFile{ outputPath };
    if( ! outputFile.open( QFile::WriteOnly )) {
        QZ_ERROR( "Qz:Cmn:Tmpl" ) << "Could not open template output file at "
                                  << outputPath;
        m_data->m_lastError = QObject::tr( "Could not open template output "
                                           "file at %1" ).arg( outputPath);
        return false;
    }
    QTextStream input{ &inputFile };
    QTextStream output{ &outputFile };
    auto tmpl = input.readAll();
    if( tmpl.isEmpty() ) {
        return true;
    }
    return process( tmpl, output );
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

    auto parseRangeField = [ & ]( const QString &token ) -> bool {
        if( token.startsWith( "range" )) {
            cursor = tokenStart;
            auto frr = input.mid( tokenStart,
                                  input.size() - tokenStart );
            range = parseRange( frr, cursor );
            if( ! range.m_valid ) {
                //since parsing of 'range' failed we restore the
                //cursor value
                cursor = cursor + token.size();
                QZ_ERROR( "Qz:Cmn:Tmpl" )
                        << "Failed to parse range of for loop";
                return false;
            }
        }
        else {
            listName = token;
        }
        return true;
    };

    while( cursor <= input.size() ) {
        if( cursor == input.size() || checkWhitespace( input, cursor )) {
            auto num = cursor - tokenStart - 1;
            if( num > 0 ) {
                auto token = input.mid( tokenStart, num );
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
                    if( ! parseRangeField( token )) {
                        break;
                    }
                }
                else if( tokenNumber == 4 ) {
                    QZ_WARN( "Qz:Cmn:Tmpl" ) << "Unknown token string "
                                                "[4] received!";
                }
                ++ tokenNumber;
            }
            tokenStart = -1;
            if( cursor == input.size() ) {
                break;
            }
        }
        else if( check( input, ":>", cursor )){
            if( tokenStart != -1 ) {
                auto token = input.mid( tokenStart, cursor - tokenStart - 2 );
                if( ! parseRangeField( token )) {
                    break;
                }
            }
            content = input.mid( cursor, input.size() - cursor /*- 1 */);
            break;
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
                replaceVariables( content, stream, provider );
            }
        }
        else {
            auto list = var( listName ).toStringList();
            foreach( const QString &item, list ) {
                value = item;
                replaceVariables( content, stream, provider );
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

const QString & AdvancedTemplateProcessor::lastError() const
{
    return m_data->m_lastError;
}

void AdvancedTemplateProcessor::reset()
{
    m_data->m_lastError = "";
}

QVariant AdvancedTemplateProcessor::var( const QString &key ) const
{
    return m_data->m_variables.value( key, QVariant{} );
}

QString AdvancedTemplateProcessor::toString( const QVariant &var ) const
{
//    if( ! var.isValid() ) {
        auto strVar = var.toString();
        if( strVar.isEmpty()  ) {
            auto list = var.toStringList();
            QTextStream varStream{ &strVar };
            foreach( QString item, list ) {
                varStream << item;
            }
        }
        return strVar;
//    }
//    return QString{};
}

void AdvancedTemplateProcessor::setError(const QString &errorString)
{
    m_data->m_lastError = errorString;
}



}
