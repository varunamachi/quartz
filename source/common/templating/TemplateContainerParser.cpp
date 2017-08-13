
#include <QString>
#include <QDomElement>

#include "Template.h"
#include "TemplateContainerParser.h"


namespace Quartz {

TemplateContainerParser::TemplateContainerParser()
{

}

TemplateContainerParser::~TemplateContainerParser()
{

}

QVector< std::shared_ptr< Template >> TemplateContainerParser::parse(
        const QString &/*content*/ )
{
    QVector< std::shared_ptr< Template >> tmpls;

    return tmpls;
}

std::unique_ptr< Template > TemplateContainerParser::parse(
        const QDomElement &/*root*/ )
{
    std::unique_ptr< Template > tmpl;

    return tmpl;
}


}
