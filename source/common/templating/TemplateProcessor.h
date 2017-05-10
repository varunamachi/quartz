#pragma once

#include <memory>

#include <QHash>

#include "../QuartzCommon.h"

class QTextStream;
class QVariant;

namespace Quartz {

class QUARTZ_COMMON_API TemplateProcessor
{
public:
    using Variables = QHash< QString, QVariant >;

    explicit TemplateProcessor( const Variables &vars );

    virtual ~TemplateProcessor();

    bool process( const QString &inputPath, const QString &outputPath );

    bool process( QTextStream &input, QTextStream &output );

    virtual bool process( QString &input, QTextStream &output );

    const QString & lastError() const;

    void reset();

protected:
    using ValueProvider =
        std::function< QString( const QString &, const QString & )>;

    bool process( const QString &input,
                  QTextStream &output,
                  ValueProvider getVar );

    QVariant var( const QString &key ) const;

    QString toString( const QVariant &variant ) const;

    void setError( const QString &errorString );

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

}
