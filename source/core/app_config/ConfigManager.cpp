#include <QVariant>

#include "ConfigManager.h"

namespace Quartz {

//class ConfigManager::Data
//{
//public:


//private:
//    QVariant m_invalid;

//};

const QVariant dummy;


ConfigManager::ConfigManager( IConfigStorageStorage *storageStragy )
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
