#pragma once

#include <functional>
#include <memory>

class QVariant;

#include "../QuartzCommon.h"

class QTextStream;

namespace Quartz {

class TemplateInstance;

class QUARTZ_COMMON_API AdvancedTemplateProcessor
{
public:
    using ValueProvider =
        std::function< QString(const QString &, const QString &)>;

    explicit AdvancedTemplateProcessor(
            const TemplateInstance *tmpl);

    ~AdvancedTemplateProcessor();

    bool replaceVariables(const QString &input,
                           QTextStream &output,
                           ValueProvider getVar);

    bool process(QTextStream &output);

    const QString & lastError() const;

    void reset();

private:
    QVariant var(const QString &key) const;

    QString toString(const QVariant &variant) const;

    void setError(const QString &errorString);

    QString processfor (const QString &input);

    QString processif (const QString &input);

    QString processBlocks(const QString &input);

    struct Data;
    std::unique_ptr<Data> m_data;
};

}
