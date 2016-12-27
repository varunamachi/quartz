

#include <core/logger/Logger.h>
#include <base/content_manager/ContentManager.h>
#include <base/selector/SelectorManager.h>
#include <base/general_selector/GeneralSelector.h>
#include <base/settings/ConfigPageManager.h>

#include "QzAppContext.h"


namespace Quartz {

struct QzAppContext::Data
{
    Logger::Logger *m_logger;

    ContentManager *m_contentManager;

    SelectorManager *m_selectorManager;

    GeneralSelector *m_nodeSelector;

    ConfigPageManager *m_configPageManager;
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
QZCONTEXT_FUNC_DEFINE( QzAppContext, GeneralSelector, nodeSelector );
QZCONTEXT_FUNC_DEFINE( QzAppContext, ConfigPageManager, configPageManager );

}
