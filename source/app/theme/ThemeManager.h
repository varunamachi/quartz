#pragma once

#include <memory>

class QString;

namespace Quartz {

class Theme;

class ThemeManager
{
public:
    explicit ThemeManager( std::shared_ptr< Theme > defaultTheme );

    ~ThemeManager();

    std::shared_ptr< Theme > defaultTheme() const;

    std::shared_ptr< Theme > theme( const QString &name ) const;

    void addTheme( std::shared_ptr< Theme > theme );

    const std::shared_ptr< Theme > current() const;

    void selectTheme( const QString &themeName );

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;

};


}
