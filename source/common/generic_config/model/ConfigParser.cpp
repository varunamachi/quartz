#include <QByteArray>
#include <QDomElement>
#include <QDomNodeList>
#include <QDomNode>
#include <QDomNamedNodeMap>

#include "ConfigParser.h"
#include "Config.h"
#include "Param.h"
#include "BooleanParam.h"
#include "ChoiceParam.h"
#include "RangeParam.h"
#include "TextParam.h"

namespace Quartz {

ParamType toParamType( const QString &strType )
{
    if( strType == "boolean" ) {
        return ParamType::Boolean;
    }
    else if( strType == "choice" ) {
        return ParamType::Choice;
    }
    else if( strType == "range" ) {
        return ParamType::Range;
    }
    return ParamType::Text;
}

QString nodeValue( const QDomNamedNodeMap &attr, const QString &key )
{
    auto domNode = attr.namedItem( key );
    if( ! domNode.isNull() ) {
        return domNode.nodeValue();
    }
    return QString{};
}

std::unique_ptr< Config > ConfigParser::parse( const QByteArray &content )
{
    if( content.isNull() ) {
        return nullptr;
    }
    std::unique_ptr< Config > config;

    return config;
}

std::unique_ptr< Config > ConfigParser::parse( const QDomElement &configRoot )
{
    std::unique_ptr< Config > config;
    auto paramList = configRoot.elementsByTagName( "param" );
    for( auto i = 0; i < paramList.size(); ++ i ) {
        auto paramNode = paramList.at( i );
        auto param = parseParam( paramNode.toElement() );
        if( param != nullptr ) {

        }
        else {
            //log error
            //continue
        }

    }
    return config;
}

std::shared_ptr< Param > ConfigParser::parseParam(
        const QDomElement &paramNode )
{
    std::shared_ptr< Param > param;
    auto attr       = paramNode.attributes();
    auto strType    = nodeValue( attr, "type" );
    auto id         = nodeValue( attr, "id" );
    auto name       = nodeValue( attr, "name" );
    auto desc       = nodeValue( attr, "description" );
    auto type       = toParamType( strType );
    if( type == ParamType::Boolean ) {
        auto strDef = nodeValue( attr, "default" );
        auto def = QString::compare( strDef, "true", Qt::CaseInsensitive );
        auto bparam = std::make_shared< BooleanParam >( id, name, desc );
        bparam->setDefaultValue( def );
    }
    else if( type == ParamType::Choice ) {

    }
    else if( type == ParamType::Range ) {

    }
    else if( type == ParamType::Text ) {

    }
    return param;
}

std::shared_ptr<Group> ConfigParser::parseGroup( const QDomElement &groupNode )
{
    std::shared_ptr< Group > group;

    return  group;
}



}
