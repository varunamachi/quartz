#pragma once

#include <core/logger/Logging.h>
#include <core/ext/Plugin.h>
#include <base/QzAppContext.h>

#include "PluginContext.h"

#undef QZ_COMMON
#undef QZ_TRACE
#undef QZ_DEBUG
#undef QZ_INFO
#undef QZ_WARN
#undef QZ_ERROR
#undef QZ_FATAL
#undef QZ_SPECIAL

#define QZ_COMMON( level, mod )                                             \
    Quartz::Logger::LogLineHolder(                                          \
        appContext()->logger(),                                             \
        new Quartz::Logger::LogMessage{ QDateTime::currentDateTime(),       \
                                        level,                              \
                                        CUR_THREAD_ID,                      \
                                        mod,                                \
                                        FUNCTION_NAME,                      \
                                        __FILE__,                           \
                                        __LINE__,                           \
                                        QString{ "" }})


#define QZ_TRACE( module ) \
    QZ_COMMON( Quartz::Logger::LogLevel::Trace, module )

#define QZ_DEBUG( module ) \
    QZ_COMMON( Quartz::Logger::LogLevel::Debug, module )

#define QZ_INFO( module ) \
    QZ_COMMON( Quartz::Logger::LogLevel::Info, module )

#define QZ_WARN( module ) \
    QZ_COMMON( Quartz::Logger::LogLevel::Warn, module )

#define QZ_ERROR( module ) \
    QZ_COMMON( Quartz::Logger::LogLevel::Error, module )

#define QZ_FATAL( module ) \
    QZ_COMMON( Quartz::Logger::LogLevel::Fatal, module )

#define QZ_SPECIAL( module ) \
    QZ_COMMON( Quartz::Logger::LogLevel::Special, module )


#define QZP_TRACE   QZ_TRACE(   plugin()->pluginId() )
#define QZP_DEBUG   QZ_DEBUG(   plugin()->pluginId() )
#define QZP_INFO    QZ_INFO(    plugin()->pluginId() )
#define QZP_WARN    QZ_WARN(    plugin()->pluginId() )
#define QZP_ERROR   QZ_ERROR(   plugin()->pluginId() )
#define QZP_FATAL   QZ_FATAL(   plugin()->pluginId() )
#define QZP_SPECIAL QZ_SPECIAL( plugin()->pluginId() )
