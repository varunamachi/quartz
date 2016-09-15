
#include "ThemeManager.h"

namespace Quartz {

class ThemeManager::Impl
{
public:

private:

};


ThemeManager::ThemeManager()
//    : m_impl( std::make_unique< Impl >() )
    : m_impl( new Impl() )

{

}


ThemeManager::~ThemeManager()
{

}

}
