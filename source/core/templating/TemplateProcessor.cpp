#include <QFile>

#include "../logger/Logging.h"

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
    bool result = false;
    auto cursor = 0;
//    auto size = ( tmpt.size() / 3 ) * 3;
//    bool replacing = false;
//    while( cursor < size ) {
//        auto val1 = tmpt[ cursor ++ ];
//        auto val2 = tmpt[ cursor ++ ];
//        auto val3 = tmpt[ cursor ++ ];
//        if( val1 == '$' && val2 == '<' && val3 == '<' ) {
//            replacing = true;
//            //do template processing
//        }
//        else {
//            output << val1 << val2 << val3;
//        }
//    }
//    auto remaining = tmpt.size() - size;
//    if( remaining != 0 ) {
//        if( remaining == 2
//                && tmpt[ cursor ] == '>'
//                && tmpt[ cursor + 1 ] == '>'
//                && replacing ) {
//            //ignore
//        }
//        else {
//            output <<
//        }
//    }
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
                //because I had eaten doller in the first if
                output << '$';
                matchCount = 0;
            }
            output << token;
        }
        ++ cursor;
        if( inMatch ) {
            matchCount = 0;
            auto unmatchCount = 0;
            QString key;
            QTextStream stream{ &key };
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
