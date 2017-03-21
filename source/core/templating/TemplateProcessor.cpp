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

bool TemplateProcessor::process(QTextStream &input, QTextStream &output)
{
    bool result = false;

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
