
#include <QString>
#include <QByteArray>
#include <QDomElement>
#include <QDomNodeList>
#include <QDomNode>
#include <QDomNamedNodeMap>

#include <core/logger/Logging.h>

#include "../generic_config/model/ConfigParser.h"
#include "../generic_config/model/Config.h"
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

std::unique_ptr< Config > parseConfig( const QDomElement &root ) {
    std::unique_ptr< Config > config;
    auto configNodeList = root.elementsByTagName( "config" );
    if( configNodeList.size() == 1 ) {
        auto configNode = configNodeList.at( 0 );
        ConfigParser configParser;
        config = configParser.parse( configNode.toElement() );
        if( config == nullptr ) {
            QZ_ERROR( "Qz:Cmn:Tmpl" )
                    << "Failed to parse template parameters";
        }
    } else {
        auto msg = configNodeList.isEmpty() ? "Could not find config tag"
                                            : "Too many config tags found";
        QZ_ERROR( "Qz:Cmn:Tmpl" ) << msg;
    }
    return config;
}

QString getTemplateContent( const QDomElement &/*root*/ )
{
    QString content;
    return content;
}

std::unique_ptr< Template > TemplateContainerParser::parse(
        const QDomElement &root )
{
    std::unique_ptr< Template > tmpl;
    auto name = root.attribute( "name" );
    if( ! name.isEmpty() ) {
        auto config = parseConfig( root );
        if( config != nullptr ) {
            auto content = getTemplateContent( root );
            tmpl = std::unique_ptr< Template >{ new Template( name, content )};
        }
    } else {
        QZ_ERROR( "Qz:Cmn:Tmpl" )
                << "Could not read the template name attribute";
    }
    return tmpl;
}


}
