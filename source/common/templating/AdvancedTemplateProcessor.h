#pragma once

#include "TemplateProcessor.h"

class QTextStream;

namespace Quartz {

class QUARTZ_COMMON_API AdvancedTemplateProcessor : public TemplateProcessor {
public:
    explicit AdvancedTemplateProcessor(
            const TemplateProcessor::Variables &vars );

    ~AdvancedTemplateProcessor();

    bool process( QString &input, QTextStream &output ) override;

private:
    QString processForeach( const QStringRef &input );

    QString processBlock( const QStringRef &input );

    struct Data;
    std::unique_ptr< Data > m_data;
};

}
