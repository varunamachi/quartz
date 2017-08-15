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
#include "Group.h"

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
    auto oNodes = choiceNode.elementsByTagName( "option" );
    for( auto i = 0; i < oNodes.size(); ++ i ) {
        auto opt = oNodes.at( i );
        auto attr = opt.attributes();
        auto name = nodeValue( attr, "name" );
        auto val = nodeValue( attr, "value" );
        if( ! name.isEmpty() && ! val.isEmpty() ) {
            param->addOption( name, val );
        }
        else {
            QZ_ERROR( "Qz:Cmn:GenParam" )
                    << "Invalid option found for choice param "
                    << param->name();
        }
    }
}

ConfigParser::ConfigParser()
{
    //Nothing here...
}

ConfigParser::~ConfigParser()
{
    //Nothing here...
}

QVector< std::shared_ptr< Config >> ConfigParser::parse(
        const QByteArray &content )
{
    QVector< std::shared_ptr< Config >> configs;
    if( content.isNull() ) {
        QZ_ERROR( "Qz:Cmn:GenParam" )
                << "Invalid content given to general param parser";
        return configs;
    }
    QDomDocument doc;
    QString errorMsg{ "" };
    int errorLine = 0;
    if( doc.setContent( content, false, &errorMsg, &errorLine )) {
        auto root = doc.documentElement();
        if( root.tagName() == "configs" ) {
            auto configLists = root.elementsByTagName( "config" );
            for( auto i = 0; i < configLists.size(); ++ i ) {
                auto configNode = configLists.at( i );
                auto config = parse( configNode.toElement() );
                if( config != nullptr ) {
                    std::shared_ptr< Config > cp = std::move( config );
                    configs.append( cp );
                }
                else {
                    QZ_ERROR( "Qz:Cmn:GenParam" )
                            << "Could not parse one of the 'config' tags";
                }
            }
            if( configLists.isEmpty() ) {
                QZ_ERROR( "Qz:Cmn:GenParam" )
                        << "Could not find 'config' tags inside 'configs'";
            }
        }
        else {
            QZ_ERROR( "Qz:Cmn:GenParam" )
                    << "Could not find root 'configs' tag";
        }
    }
    else {
        QZ_ERROR( "Qz:Cmn:GenParam" )
                << "Failed to read config XML content at " << errorLine
                << " Msg: " << errorMsg;

    }
    return configs;
}

std::unique_ptr< Config > ConfigParser::parse( const QDomElement &configRoot )
{
    std::unique_ptr< Config > config;
    auto name = configRoot.attribute( "name" );
    auto id   = configRoot.attribute( "id" );
    auto configName = configRoot.tagName();
    if( configName == "config" && ! name.isEmpty() && ! id.isEmpty() ) {
        config = std::unique_ptr< Config >{ new Config{ id, name }};
        auto paramList = configRoot.elementsByTagName( "param" );
        for( auto i = 0; i < paramList.size(); ++ i ) {
            auto paramNode = paramList.at( i );
            auto param = parseParam( paramNode.toElement() );
            if( param != nullptr ) {
                config->registerParam( param.get() );
                config->addChildParameter( param );
            }
            else {
                QZ_ERROR( "Qz:Cmn:GenParam" )
                        << "Failed to parse top level parameter for config "
                        << name;
            }
        }
        auto groupList = configRoot.elementsByTagName( "group" );
        for( auto i = 0; i < groupList.size(); ++ i ) {
            auto groupNode = groupList.at( i );
            auto group = parseGroup( *config.get(), groupNode.toElement() );
            if( group != nullptr ) {
                config->addGroup( group );
            }
            else {
                QZ_ERROR( "Qz:Cmn:GenParam" )
                        << "Failed to parse a high level group for config "
                        << name;
            }
        }
    }
    else {
        QZ_ERROR( "Qz:Cmn:GenParam" ) << "Invalid 'config' found";
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
            QZ_ERROR( "Qz:Cmn:GenParam" )
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
        Config &config,
        const QDomElement &groupNode )
{
    std::shared_ptr< Group > group;
    auto name   = groupNode.attribute( "name" );
    auto id     = groupNode.attribute( "id" );
    auto desc   = groupNode.attribute( "description" );
    if( ! id.isEmpty() && ! name.isEmpty() ) {
        group = std::make_shared< Group >( id, name, desc );
        auto pNodes = groupNode.elementsByTagName( "param" );
        for( auto i = 0; i < pNodes.size(); ++ i ) {
            auto pn = pNodes.at( i );
            auto param = parseParam( pn.toElement() );
            if( param != nullptr ) {
                config.registerParam( param.get() );
                group->addParam( param );
            }
            else {
                QZ_ERROR( "Qz:Cmn:GenParam" )
                        << "Invalid parameter found in group " << name;
            }
        }
        auto gNodes = groupNode.elementsByTagName( "group" );
        for( auto i = 0; i < gNodes.count(); ++ i ) {
            auto gn = gNodes.at( i );
            auto subGroup = parseGroup( config, gn.toElement() );
            if( subGroup != nullptr ) {
                group->addSubGroup( subGroup );
            }
            else {
                QZ_ERROR( "Qz:Cmn:GenParam" )
                        << "Invalid sub group found under group " << name;
            }
        }
    }
    return  group;
}

}
