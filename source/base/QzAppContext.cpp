

#include <core/logger/Logger.h>
#include <base/content_manager/ContentManager.h>
#include <base/selector/SelectorManager.h>
#include <base/selector/NodeSelector.h>

#include "QzAppContext.h"


namespace Quartz {

struct QzAppContext::Data
{
    Logger::Logger *m_logger;

    ContentManager *m_contentManager;

    SelectorManager *m_selectorManager;

    NodeSelector *m_nodeSelector;
};

QzAppContext::QzAppContext()
//    : m_data( std::make_unique< Data >{ })
    : m_data( new Data{ })
{

}

QzAppContext::~QzAppContext()
{

}

QZCONTEXT_FUNC_DEFINE( QzAppContext, ContentManager, contentManager );
QZCONTEXT_FUNC_DEFINE( QzAppContext, SelectorManager, selectorManager );
QZCONTEXT_FUNC_DEFINE( QzAppContext, NodeSelector, nodeSelector );




}