#pragma once

#include <memory>

#include <QString>

namespace Quartz {

class TemplateInfo
{
public:
    explicit TemplateInfo();

    ~TemplateInfo();

    void addVariable( const QString &key, const QString &value );

    void addTemplate( const QString &templateName, const QString &content );
    
    QStringList templateNames() const;

    QString templateFor( const QString &templateName ) const;

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
