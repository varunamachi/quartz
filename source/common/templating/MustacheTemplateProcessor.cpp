
#include <QTextStream>


#include "third_party/Mustache.h"
#include "Template.h"
#include "TemplateInstance.h"
#include "MustacheTemplateProcessor.h"


namespace Quartz {

struct MustacheTemplateProcessor::Data {
    explicit Data(const TemplateInstance *tmpl)
        : m_templateInst(tmpl)
    {

    }

    const TemplateInstance *m_templateInst;

    QString m_lastError;
};

MustacheTemplateProcessor::MustacheTemplateProcessor(
        const TemplateInstance *tmpl)
    : m_data(std::make_unique<Data>(tmpl))
{

}

MustacheTemplateProcessor::~MustacheTemplateProcessor()
{

}

bool MustacheTemplateProcessor::process(QTextStream &stream)
{
    auto hash = m_data->m_templateInst->allParams();
    auto content = m_data->m_templateInst->instanceOf()->content();
    Mustache::Renderer renderer;
    Mustache::QtVariantContext context(hash);
    stream << renderer.render(content, &context);
    if (renderer.errorPos() == -1) {
        m_data->m_lastError = renderer.error();
        return false;
    }
    return true;
}

const QString & MustacheTemplateProcessor::lastError() const
{
    return m_data->m_lastError;
}

void MustacheTemplateProcessor::reset()
{
    m_data->m_templateInst = nullptr;
    m_data->m_lastError = "";
}

}
