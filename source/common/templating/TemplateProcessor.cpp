#include <QFile>

#include <core/logger/Logging.h>
#include <core/utils/Constants.h>

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

bool TemplateProcessor::process( QString &input, QTextStream &output )
{
    return process( input, output,
                    [ & ]( const QString &key, const QString &def ) -> QString {
        auto var = m_data->m_variables.value( key, def );
        return this->toString( var );
    });
}

bool TemplateProcessor::process(
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

const QString & TemplateProcessor::lastError() const
{
    return m_data->m_lastError;
}

void TemplateProcessor::reset()
{
    m_data->m_lastError = "";
}

QVariant TemplateProcessor::var( const QString &key ) const
{
    return m_data->m_variables.value( key, QVariant{} );
}

QString TemplateProcessor::toString( const QVariant &var ) const
{
    if( ! var.isValid() ) {
        auto strVar = var.toString();
        if( strVar.isEmpty()  ) {
            auto list = var.toStringList();
            QTextStream varStream{ &strVar };
            foreach( QString item, list ) {
                varStream << item;
            }
        }
        return strVar;
    }
    return QString{};
}

void TemplateProcessor::setError(const QString &errorString)
{
    m_data->m_lastError = errorString;
}


}
