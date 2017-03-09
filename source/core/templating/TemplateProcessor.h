#pragma once

#include <memory>

#include <QHash>

namespace Quartz {

class TemplateProcessor final
{
public:
    using Variables = QHash< QString, QString >;

    explicit TemplateProcessor( const Variables &vars );

    ~TemplateProcessor();

    bool process( const QString &inputPath,
                  const QString &outputPath );

    const QString & lastError() const;

    void reset();

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

}
