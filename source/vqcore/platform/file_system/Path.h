#pragma once

#include <memory>

namespace Vam {

class Path
{
public:

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;
};


}
