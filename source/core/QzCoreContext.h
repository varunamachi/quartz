#pragma once

#include <memory>

#include "QuartzCore.h"

#define QZCONTEXT_FUNC_DECL( ClassName, VarName ) \
    void set##ClassName( ClassName *VarName ); \
    ClassName * VarName() const; \
    bool has##ClassName() const

#define QZCONTEXT_FUNC_DECL_NS( NameSpace, ClassName, VarName ) \
    void set##ClassName( NameSpace::ClassName *VarName ); \
    NameSpace::ClassName * VarName() const; \
    bool has##ClassName() const

#define QZCONTEXT_FUNC_DEFINE_NS( Context, NameSpace, ClassName, VarName ) \
    void Context::set##ClassName( NameSpace::ClassName *VarName ) { \
        m_data->m_##VarName = VarName; \
    } \
    NameSpace::ClassName * Context::VarName() const { \
        return m_data->m_##VarName; \
    } \
    bool Context::has##ClassName() const { \
        return m_data->m_##VarName != nullptr; \
    }

#define QZCONTEXT_FUNC_DEFINE( Context, ClassName, VarName ) \
    void Context::set##ClassName( ClassName *VarName ) { \
        m_data->m_##VarName = VarName; \
    } \
    ClassName * Context::VarName() const { \
        return m_data->m_##VarName; \
    } \
    bool Context::has##ClassName() const { \
        return m_data->m_##VarName != nullptr; \
    }

namespace Quartz {

namespace Logger {
    class Logger;
}

class QUARTZ_CORE_API QzCoreContext
{
public:
    QzCoreContext();

    ~QzCoreContext();

    QZCONTEXT_FUNC_DECL_NS( Logger, Logger, logger );

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};



}
