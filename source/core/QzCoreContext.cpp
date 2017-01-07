
#include "logger/Logging.h"
#include "extension_system/PluginManager.h"
#include "app_config/ConfigManager.h"
#include "QzCoreContext.h"

namespace Quartz {

std::unique_ptr< QzCoreContext > QzCoreContext::s_instance{ nullptr };

struct QzCoreContext::Data
{

    Data()
        : m_logger{ nullptr }
        , m_pluginManager{ nullptr }
        , m_configManager{ nullptr }
    {

    }

    Logger::Logger *m_logger;

    PluginManager *m_pluginManager;

    ConfigManager *m_configManager;
};

QZCONTEXT_FUNC_DEFINE_NS( QzCoreContext, Logger, Logger, logger );
QZCONTEXT_FUNC_DEFINE( QzCoreContext, PluginManager, pluginManager );
QZCONTEXT_FUNC_DEFINE( QzCoreContext, ConfigManager, configManager );

QzCoreContext::QzCoreContext()
    : m_data{ new Data{ }}
{

}

QzCoreContext::~QzCoreContext()
{

}

}
