#pragma once

#include <memory>

#include <QVector>

class QDomElement;

namespace Quartz {

class Template;

class TemplateContainerParser
{
public:
    TemplateContainerParser();

    ~TemplateContainerParser();

    QVector< std::shared_ptr< Template >> parse( const QString &content );

    std::unique_ptr< Template > parse( const QDomElement &root );

private:
};

}
