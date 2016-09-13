
#include <QString>
#include <QVariant>
#include <QtXml/QDomDocument>


#include "XMLConfigLoader.h"

namespace Quartz {

XMLConfigLoader::XMLConfigLoader( AbstractConfigLoader::StoreFunc storeFunc )
    : AbstractConfigLoader( storeFunc )
{

}


XMLConfigLoader::~XMLConfigLoader()
{

}


bool XMLConfigLoader::load( const QString &filePath ) const
{

}




}
