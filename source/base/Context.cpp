

#include <core/logger/Logger.h>
#include <base/content_manager/ContentManager.h>
#include <base/selector/SelectorManager.h>
#include <base/selector/NodeSelector.h>

#include "Context.h"

#define QZCONTEXT_FUNC_DEFINE( ClassName, VarName ) \
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

struct Context::Data
{
    TntLogger *m_logger;

    ContentManager *m_contentManager;

    SelectorManager *m_selectorManager;

    NodeSelector *m_nodeSelector;
};

Context::Context()
//    : m_data( std::make_unique< Data >{ })
    : m_data( new Data{ })
{

}

Context::~Context()
{

}

QZCONTEXT_FUNC_DEFINE( TntLogger, logger );
QZCONTEXT_FUNC_DEFINE( ContentManager, contentManager );
QZCONTEXT_FUNC_DEFINE( SelectorManager, selectorManager );
QZCONTEXT_FUNC_DEFINE( NodeSelector, nodeSelector );




}
