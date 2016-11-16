#pragma once

#include <memory>

#include "QuartzBase.h"

namespace Quartz {

class ContentManager;
class SelectorManager;
class NodeSelector;
class PlugginManager;
namespace Logger {
    class Logger;
}


#define QZCONTEXT_FUNC_DECL( ClassName, VarName ) \
    void set##ClassName( ClassName *VarName ); \
    ClassName * VarName() const; \
    bool has##ClassName() const

#define QZCONTEXT_FUNC_DECL_NS( NameSpace, ClassName, VarName ) \
    void set##ClassName( NameSpace::ClassName *VarName ); \
    NameSpace::ClassName * VarName() const; \
    bool has##ClassName() const

class QUARTZ_BASE_API Context
{
public:
    explicit Context();

    ~Context();

    QZCONTEXT_FUNC_DECL_NS( Logger, Logger, logger );
    QZCONTEXT_FUNC_DECL( ContentManager, contentManager );
    QZCONTEXT_FUNC_DECL( SelectorManager, selectorManager );
    QZCONTEXT_FUNC_DECL( NodeSelector, nodeSelector );

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
