#pragma once

#include <memory>

#include <QHash>

#include "../QuartzCore.h"

class QTextStream;

namespace Quartz {

class QUARTZ_CORE_API TemplateProcessor final
{
public:
    using Variables = QHash< QString, QString >;

    explicit TemplateProcessor( const Variables &vars );

    ~TemplateProcessor();

    bool process( const QString &inputPath, const QString &outputPath );

    bool process( QTextStream &input, QTextStream &output );

    const QString & lastError() const;

    void reset();

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

}
