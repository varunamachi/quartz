#pragma once

#include <memory>

#include "../QuartzCommon.h"

class QTextStream;

namespace Quartz {

class TemplateInstance;

class QUARTZ_COMMON_API MustacheTemplateProcessor
{
public:
    explicit MustacheTemplateProcessor(const TemplateInstance *tmpl);

    ~MustacheTemplateProcessor();

    bool process(QTextStream &stream);

    const QString & lastError() const;

    void reset();

private:
    struct Data;
    std::unique_ptr<Data> m_data;

};

}
