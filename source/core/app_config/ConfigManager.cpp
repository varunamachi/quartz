#include <QVariant>

#include "IConfigStorageStrategy.h"
#include "ConfigManager.h"

namespace Quartz {

class ConfigManager::Data
{
public:
    explicit Data( std::unique_ptr< IConfigStorageStrategy > storage )
        : m_storage( std::move( storage ))
    {

    }

    const QVariant & value( QString &key ) const
    {

    }




private:
    QVariant m_invalid;

    QHash< QString, QVariant > m_cache;

    std::unique_ptr< IConfigStorageStrategy > m_storage;

};

const QVariant dummy;


ConfigManager::ConfigManager(
        std::unique_ptr< IConfigStorageStrategy > storageStragy )
//    : m_data( std::make_unique< ConfigManager::Data >(
//                  std::move( storageStragy )))
    : m_data( new ConfigManager::Data( std::move( storageStragy )))

{

}


ConfigManager::~ConfigManager()
{

}


void  ConfigManager::clearCache()
{

}


void  ConfigManager::store( const QString &key, const QVariant &variant )
{

}

const QVariant & ConfigManager::retrieve( const QString &key )
{
    return dummy;
}


bool  ConfigManager::has( const QString &key )
{
    return false;
}


void  ConfigManager::loadFromFile( const QString &path )
{

}



}
