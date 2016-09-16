#pragma once

#include <memory>

namespace Quartz {

class Theme;

class ThemeManager
{
public:
    explicit ThemeManager( std::shared_ptr< Theme > defaultTheme );

    ~ThemeManager();

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;

};


}
