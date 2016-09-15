#pragma once

#include <memory>

namespace Quartz {

class ThemeManager
{
public:
    ThemeManager();

    ~ThemeManager();

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;

};


}
