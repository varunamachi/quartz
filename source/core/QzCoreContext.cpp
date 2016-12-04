
#include "logger/Logging.h"
#include "QzCoreContext.h"

namespace Quartz {

std::unique_ptr< QzCoreContext > QzCoreContext::s_instance{ nullptr };

struct QzCoreContext::Data
{

    Logger::Logger *m_logger;
};

QZCONTEXT_FUNC_DEFINE_NS( QzCoreContext, Logger, Logger, logger );

QzCoreContext::QzCoreContext()
    : m_data{ new Data{ }}
{

}

QzCoreContext::~QzCoreContext()
{

}

}
