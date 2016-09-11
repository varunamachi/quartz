
#include "XMLConfigLoader.h"

namespace Quartz {

class XMLConfigLoader::Impl
{
public:
    explicit Impl( const QString &filePath )
        : m_filePath( filePath )
    {

    }

    void load( IConfigBatchLoader::StoreFunc &storeFunc );

private:
    QString m_filePath;
};



void XMLConfigLoader::Impl::load( IConfigBatchLoader::StoreFunc &storeFunc )
{

}



//##### Loader - proper
XMLConfigLoader::XMLConfigLoader( const QString &filePath )
//    : m_impl( std::make_unique< Impl >( filePath ))
    : m_impl( new Impl( filePath ))
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
