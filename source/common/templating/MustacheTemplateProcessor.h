#pragma once

#include <memory>

#include <QVariant>

#include "../QuartzCommon.h"

class QIODevice;

namespace Quartz {

class TemplateInstance;

class QUARTZ_COMMON_API MustacheTemplateProcessor {
public:
    explicit MustacheTemplateProcessor();

    ~MustacheTemplateProcessor();

    QString process(const QString& content, QVariantHash vars);

    const QString& lastError() const;

    void reset();

    bool hasError() const;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

} // namespace Quartz
