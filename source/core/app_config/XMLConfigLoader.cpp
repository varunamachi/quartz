

#include <QString>
#include <QVariant>
#include <QFile>
#include <QtXml/QDomDocument>

#include "../logger/Logger.h"
#include "XMLConfigLoader.h"

namespace Quartz {

static QVariant variantFrom( const QDomNode &type,
                             const QDomNode &value )
{
    return QVariant{ value.nodeValue() };
}

XMLConfigLoader::XMLConfigLoader( AbstractConfigLoader::StoreFunc storeFunc )
    : AbstractConfigLoader( storeFunc )
{

}


XMLConfigLoader::~XMLConfigLoader()
{

}


bool XMLConfigLoader::load( const QByteArray content ) const
{
    if( ! content.isNull() ) {
        QZ_ERROR( "Qz:Core:Config" )
                << "XML Config Loader: Invalid content given";
        return false;
    }
    bool result = false;
    QDomDocument doc;
    QString errorMsg { "" };
    int errorLine = 0;
    if( doc.setContent( content, false, &errorMsg, &errorLine )) {
        auto root = doc.documentElement();
        if( root.tagName() != "quartz-config" ) {
            QZ_ERROR( "Qz:Core:Config" )
                    << "XML Config Loader: Could not find tag 'quartz-config'";
            return false;
        }
        auto configList = root.elementsByTagName( "config" );
        for( int i = 0; i < configList.size(); ++ i ) {
            auto configNode = configList.at( i );
            auto domainNode = configNode.parentNode();
            QString domain = "";
            if( domainNode.nodeName() == "domain" ) {
                auto attrMap = domainNode.attributes();
                auto domainNameAttr = attrMap.namedItem( "name" );
                if( ! domainNameAttr.isNull() ) {
                    domain = domainNameAttr.nodeValue();
                }
            }
            auto configAttrMap = configNode.attributes();
            auto keyAttr  = configAttrMap.namedItem( "name" );
            auto valAttr  = configAttrMap.namedItem( "value" );
            auto typeAttr = configAttrMap.namedItem( "type" );
            if( keyAttr.isNull() || valAttr.isAttr() ) {
                QZ_WARN( "Qz:Core:Config" )
                        << "XML Config Loader: Invalid attribute found in "
                           "domain " << ( domain.isEmpty() ? "[GLOBAL]"
                                                           : domain );
            }
            else {
                storeFunc()( domain,
                             keyAttr.nodeValue(),
                             variantFrom( typeAttr, valAttr ));
            }
        }
    }
    else {
        QZ_ERROR( "Qz:Core:Config" )
                << "XML Config Loader: Validation failed: "
                << errorMsg << " - Error Line: " << errorLine;
    }
    return false;
}




}
