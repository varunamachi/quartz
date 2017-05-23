#pragma once

#include "TemplateProcessor.h"

class QTextStream;

namespace Quartz {

class QUARTZ_COMMON_API AdvancedTemplateProcessor {
public:
    using ValueProvider =
        std::function< QString( const QString &, const QString & )>;

    explicit AdvancedTemplateProcessor(
            const TemplateProcessor::Variables &vars );

    ~AdvancedTemplateProcessor();

    bool replaceVariables( const QString &input,
                           QTextStream &output,
                           ValueProvider getVar );

    bool process( const QString &inputPath, const QString &outputPath );

    bool process( QString &input, QTextStream &output );

    const QString & lastError() const;

    void reset();

private:
    QVariant var( const QString &key ) const;

    QString toString( const QVariant &variant ) const;

    void setError( const QString &errorString );

    QString processFor( const QString &input );

    QString processIf( const QString &input );

    QString processBlocks( const QString &input );

    struct Data;
    std::unique_ptr< Data > m_data;
};

}
