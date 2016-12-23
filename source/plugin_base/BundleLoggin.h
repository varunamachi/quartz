#pragma once

#include <core/logger/Logging.h>
#include <core/extension_system/AbstractPluginBundle.h>
#include <base/QzAppContext.h>

#include "BundleContext.h"

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
        new Quartz::Logger::LogMessage( QDateTime::currentDateTime(),       \
                                        level,                              \
                                        CUR_THREAD_ID,                      \
                                        mod,                                \
                                        FUNCTION_NAME,                      \
                                        __LINE__,                           \
                                        QString{ "" }))


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


#define QZP_TRACE   QZ_TRACE(   pluginBundle()->bundleId() )
#define QZP_DEBUG   QZ_DEBUG(   pluginBundle()->bundleId() )
#define QZP_INFO    QZ_INFO(    pluginBundle()->bundleId() )
#define QZP_WARN    QZ_WARN(    pluginBundle()->bundleId() )
#define QZP_ERROR   QZ_ERROR(   pluginBundle()->bundleId() )
#define QZP_FATAL   QZ_FATAL(   pluginBundle()->bundleId() )
#define QZP_SPECIAL QZ_SPECIAL( pluginBundle()->bundleId() )
