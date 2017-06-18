#pragma once

#include <core/logger/Logging.h>

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
        Quartz::Plugin::BundleContext::instance()->appContext()->logger(),  \
        new Quartz::Logger::LogMessage( QDateTime::currentDateTime(),       \
                                        level,                              \
                                        CUR_THREAD_ID,                      \
                                        mod,                                \
                                        FUNCTION_NAME,                      \
                                        __LINE__,                           \
                                        QString{ "" }))


#define QZ_TRACE( module ) \
    QZ_COMMON( Quartz::Logger::LogLevel::Trace, module )

#define QZP_DEBUG( module ) \
    QZ_COMMON( Quartz::Logger::LogLevel::Debug, module )

#define QZP_INFO( module ) \
    QZ_COMMON( Quartz::Logger::LogLevel::Info, module )

#define QZP_WARN( module ) \
    QZ_COMMON( Quartz::Logger::LogLevel::Warn, module )

#define QZP_ERROR( module ) \
    QZ_COMMON( Quartz::Logger::LogLevel::Error, module )

#define QZP_FATAL( module ) \
    QZ_COMMON( Quartz::Logger::LogLevel::Fatal, module )

#define QZP_SPECIAL( module ) \
    QZ_COMMON( Quartz::Logger::LogLevel::Special, module )
