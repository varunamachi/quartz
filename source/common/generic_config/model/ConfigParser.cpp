#include <QByteArray>
#include <QDomElement>
#include <QDomNodeList>
#include <QDomNode>
#include <QDomNamedNodeMap>

#include <core/logger/Logging.h>

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

void parseOptions( ChoiceParam *param, const QDomElement &choiceNode )
{

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
    auto strDef     = nodeValue( attr, "default" );
    auto type       = toParamType( strType );
    if( type == ParamType::Boolean ) {
        auto def = QString::compare( strDef, "true", Qt::CaseInsensitive );
        auto bparam = std::make_shared< BooleanParam >( id, name, desc );
        bparam->setDefaultValue( def );
        param = bparam;
    }
    else if( type == ParamType::Choice ) {
        auto def = strDef.toInt();
        auto cparam = std::make_shared< ChoiceParam >( id, name, desc );
        cparam->setDefaultIndex( def );
        param = cparam;
    }
    else if( type == ParamType::Range ) {
        auto def = strDef.toInt();
        auto min = nodeValue( attr, "min" ).toInt();
        auto max = nodeValue( attr, "max" ).toInt();
        auto inc = nodeValue( attr, "inc" ).toInt();
        if( min < max && inc != 0 ) {
            auto rparam = std::make_shared< RangeParam >( id, name, desc );
            rparam->setDefaultValue( def );
            rparam->setMin( min );
            rparam->setMax( max );
            rparam->setIncrement( inc );
            param = rparam;
        }
        else {
            QZ_ERROR( "Cmn:GenParam" )
                    << "Failed to parse range parameter with ID " << id;
        }
    }
    else if( type == ParamType::Text ) {
        auto tparam = std::make_shared< TextParam >( id, name, desc );
        tparam->setDefaultValue( strDef );
        param = tparam;
    }
    return param;
}

std::shared_ptr< Group > ConfigParser::parseGroup(
        const QDomElement &groupNode )
{
    std::shared_ptr< Group > group;
    //parse group attributes
    //create group object
    //iterate and process the param tags
    //iterate and parse group tag - recursive
    return  group;
}



}
