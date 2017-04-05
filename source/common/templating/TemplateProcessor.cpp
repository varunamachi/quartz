#include <QFile>

#include <core/logger/Logging.h>

#include "TemplateProcessor.h"

namespace Quartz {

struct TemplateProcessor::Data
{
    explicit Data( const TemplateProcessor::Variables &vars )
        : m_variables{ vars }
        , m_lastError{ "" }
    {

    }

    TemplateProcessor::Variables m_variables;

    QString m_lastError;
};

TemplateProcessor::TemplateProcessor( const Variables &vars )
    : m_data{ new Data{ vars }}
{

}

TemplateProcessor::~TemplateProcessor()
{
}

bool TemplateProcessor::process( const QString &inputPath,
                                 const QString &outputPath )
{
    QFile inputFile{ inputPath };
    if( ! inputFile.open( QFile::ReadOnly )) {
        QZ_ERROR( "Qz:Core" ) << "Failed to open template file at "
                              << inputPath;
        m_data->m_lastError = QObject::tr( "Could not open template input "
                                           "file at %1" ).arg( inputPath);
        return false;
    }
    QFile outputFile{ outputPath };
    if( ! outputFile.open( QFile::WriteOnly )) {
        QZ_ERROR( "Qz:Core" ) << "Could not open template output file at "
                              << outputPath;
        m_data->m_lastError = QObject::tr( "Could not open template output "
                                           "file at %1" ).arg( outputPath);
        return false;
    }
    QTextStream input{ &inputFile };
    QTextStream output{ &outputFile };
    return process( input, output );

}

bool TemplateProcessor::process( QTextStream &input, QTextStream &output )
{
    auto tmpl = input.readAll();
    if( tmpl.isEmpty() ) {
        return true;
    }
    bool result = true;
    auto cursor = 0;
    auto matchCount = 0;
    auto inMatch = false;
    while( cursor < tmpl.size() ) {
        auto token = tmpl[ cursor ];
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
            while( inMatch && cursor < tmpl.size() ) {
                token = tmpl[ cursor ];
                if( unmatchCount == 0 && token == '>' ) {
                    ++ unmatchCount;
                }
                else if( unmatchCount == 1 && token == '$' ) {
                    stream.flush();
                    auto def = "$<" + key + ">$";
                    auto var = m_data->m_variables.value( key, def );
                    output << var;
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

const QString & TemplateProcessor::lastError() const
{
    return m_data->m_lastError;
}

void TemplateProcessor::reset()
{
    m_data->m_lastError = "";
}


}
