
#include <QTextStream>


#include "third_party/Mustache.h"
#include "Template.h"
#include "TemplateInstance.h"
#include "MustacheTemplateProcessor.h"


namespace Quartz {

struct MustacheTemplateProcessor::Data {
    explicit Data() {     }
    QTextStream m_stream;

    QString m_lastError;
};

MustacheTemplateProcessor::MustacheTemplateProcessor()
    : m_data(std::make_unique<Data>())
{

}

MustacheTemplateProcessor::~MustacheTemplateProcessor()
{

}

QString MustacheTemplateProcessor::process(const QString &content,
                                           QVariantHash hash)
{
    QString output;
    QTextStream stream(&output);
    Mustache::Renderer renderer;
    Mustache::QtVariantContext context(hash);
    stream << renderer.render(content, &context);
    if (renderer.errorPos() != -1) {
        m_data->m_lastError = renderer.error();
        output = "";
    }
    return output;
}

const QString & MustacheTemplateProcessor::lastError() const
{
    return m_data->m_lastError;
}

void MustacheTemplateProcessor::reset()
{
    m_data->m_lastError = "";
}

bool MustacheTemplateProcessor::hasError() const
{
    return m_data->m_lastError != "";
}

}
