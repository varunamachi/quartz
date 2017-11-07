#pragma once

#include <memory>

#include <QVector>

#include "../QuartzCommon.h"

class QDomElement;

namespace Quartz {

class Template;

class QUARTZ_COMMON_API TemplateContainerParser
{
public:
    TemplateContainerParser();

    ~TemplateContainerParser();

    QVector< std::shared_ptr< Template >> parse( const QString &content );

    std::unique_ptr< Template > parse( const QDomElement &root );

private:
};

}
