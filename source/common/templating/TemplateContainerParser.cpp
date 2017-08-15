
#include <QFile>
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
        const QString &content )
{
    QVector< std::shared_ptr< Template >> tmpls;
    if( content.isNull() ) {
        QZ_ERROR( "Qz:Cmn:Tmpl" )
                << "Invalid content given to general param parser";
        return tmpls;
    }
    QDomDocument doc;
    QString errorMsg{ "" };
    int errorLine = 0;
    if( doc.setContent( content, false, &errorMsg, &errorLine )) {
        auto root = doc.documentElement();
        if( root.tagName() == "templates" ) {
            auto tmplLists = root.elementsByTagName( "template" );
            for( auto i = 0; i < tmplLists.size(); ++ i ) {
                auto tmplNode = tmplLists.at( i );
                auto tmpl = parse( tmplNode.toElement() );
                if( tmpl != nullptr ) {
                    std::shared_ptr< Template > cp = std::move( tmpl );
                    tmpls.append( cp );
                }
                else {
                    QZ_ERROR( "Qz:Cmn:Tmpl" )
                            << "Could not parse one of the 'template' tags";
                }
            }
            if( tmplLists.isEmpty() ) {
                QZ_ERROR( "Qz:Cmn:Tmpl" )
                        << "Could not find 'template' tags inside 'templates'";
            }
        }
        else {
            QZ_ERROR( "Qz:Cmn:Tmpl" )
                    << "Could not find root 'templates' tag";
        }
    }
    else {
        QZ_ERROR( "Qz:Cmn:Tmpl" )
                << "Failed to read config XML content at " << errorLine
                << " Msg: " << errorMsg;

    }
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

QString getTemplateContent( const QDomElement &root )
{
    QString content;
    auto cntNodeList = root.elementsByTagName( "content" );
    bool gotContent = false;
    if( cntNodeList.size() == 1 ) {
        auto children = cntNodeList.at( 0 ).toElement().childNodes();
        for( auto i = 0; i < children.size(); ++ i ) {
            auto child = children.at( i );
            if( child.isCDATASection() ) {
                auto cdata = child.toCDATASection();
                content = cdata.data();
                gotContent = true;
                break;
            }
            else if( child.nodeName() == "file" ) {
                auto path = child.toElement().attribute( "path" );
                QFile file{ path };
                if( file.open( QFile::ReadOnly )) {
                    content = file.readAll();
                    gotContent = true;
                    break;
                }
                else {
                    QZ_ERROR( "Qz:Cmn:Tmpl" )
                            << "Failed to open template file at '"
                            << path << "'";
                }
            }
        }
    }
    else {
        auto msg = cntNodeList.isEmpty() ? "Could not find valid content tag"
                                         : "Found too many content tags";
        QZ_ERROR( "Qz:Cmn:Tmpl" ) << msg;
    }
    if( ! gotContent ) {
        QZ_ERROR( "Qz:Cmn:Tmpl" ) << "Failed to fetch template content";
    }

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
            if( ! content.isEmpty() ) {
                tmpl = std::unique_ptr< Template >{
                        new Template{ name, content }};
            }
            else {
                QZ_ERROR( "Qz:Cmn:Tmpl" )
                        << "Found empty template content";
            }
        }
    } else {
        QZ_ERROR( "Qz:Cmn:Tmpl" )
                << "Could not read the template name attribute";
    }
    return tmpl;
}


}
