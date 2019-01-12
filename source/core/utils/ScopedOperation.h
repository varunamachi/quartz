#pragma once

#include <functional>

#include "Macros.h"

namespace Quartz {

class ScopedOperation
{
public:
    ScopedOperation(std::function< void() > entry,
                     std::function< void() > exit)
        : m_exitTask(exit)
    {
        if (entry != nullptr) {
            entry();
        }
    }

    ~ScopedOperation()
    {
        if (m_exitTask) {
            m_exitTask();
        }
    }

private:
    std::function< void() > m_exitTask;
};

}


#define AT_SCOPE_EXIT(x) \
    Quartz::ScopedOperation LINE_VAR(tnt_scpop)(nullptr, [ & ]() { x; })

#define SCOPE_LIMIT(x, y) \
    Quartz::ScopedOperation LINE_VAR(tnt_scpop)([ & ]() { x; },  \
                                                [ & ]() { y; })
