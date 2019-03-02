#pragma once

#include <memory>

namespace Quartz {

class Theme;

class ThemeParser
{
public:
    explicit ThemeParser();

    std::unique_ptr<Theme> parse();

private:

};

}
