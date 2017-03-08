#pragma once

#include <memory>
#include <iostream>

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
class PluginManager;
class ConfigManager;

class QUARTZ_CORE_API QzCoreContext
{
public:
    QzCoreContext();

    virtual ~QzCoreContext();

    QZCONTEXT_FUNC_DECL_NS( Logger, Logger, logger );
    QZCONTEXT_FUNC_DECL( PluginManager, pluginManager );
    QZCONTEXT_FUNC_DECL( ConfigManager, configManager );

    static QzCoreContext * get()
    {
        return s_instance.get();
    }

    static void setInstance( std::unique_ptr< QzCoreContext > &&instance )
    {
        s_instance = std::move( instance );
    }

private:
    static std::unique_ptr< QzCoreContext > s_instance;

    struct Data;
    std::unique_ptr< Data > m_data;
};


template< typename T >
static T * context()
{
   return  dynamic_cast< T *>( QzCoreContext::get() );
}

}
