
#include "AbstractConfigLoader.h"

namespace Quartz {

struct AbstractConfigLoader::Data
{
    explicit Data( StoreFunc func )
        : m_func( func )
    {

    }

    StoreFunc m_func;
};

AbstractConfigLoader::~AbstractConfigLoader()
{

}

AbstractConfigLoader::StoreFunc AbstractConfigLoader::storeFunc() const
{
    return m_data->m_func;
}

AbstractConfigLoader::AbstractConfigLoader(
        AbstractConfigLoader::StoreFunc storeFunc )
    : m_data{ new Data{ storeFunc }}
{

}



}
