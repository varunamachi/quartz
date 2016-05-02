#pragma once

#include <memory>

namespace Vam {

class JobHandler final
{
public:
    JobHandler();

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;

};

}
