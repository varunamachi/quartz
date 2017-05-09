#pragma once

#include <memory>

#include <QHash>

#include "../QuartzCommon.h"

class QTextStream;

namespace Quartz {

class QUARTZ_COMMON_API TemplateProcessor
{
public:
    using Variables = QHash< QString, QString >;

    explicit TemplateProcessor( const Variables &vars );

    ~TemplateProcessor();

    bool process( const QString &inputPath, const QString &outputPath );

    bool process( QTextStream &input, QTextStream &output );

    virtual bool process( QString &input, QTextStream &output );

    const QString & lastError() const;

    void reset();

protected:
    QString expand( const QString &key ) const;

    void setError( const QString &errorString );

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

}
