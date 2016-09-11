
#include "XMLConfigLoader.h"

namespace Quartz {



//##### Loader - proper
XMLConfigLoader::XMLConfigLoader( const QString &filePath )
{

}

XMLConfigLoader::~XMLConfigLoader()
{

}

void XMLConfigLoader::load( IConfigBatchLoader::StoreFunc storeFunc )
{
    m_impl->load( storeFunc );
}



}
