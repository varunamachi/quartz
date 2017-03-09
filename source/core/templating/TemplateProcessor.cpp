
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

bool TemplateProcessor::process( const QString &/*inputPath*/,
                                 const QString &/*outputPath*/ )
{
    bool result = false;
    m_data->m_lastError = "";

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
