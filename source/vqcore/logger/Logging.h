#pragma once

#include <QTextStream>

#include "LogMessage.h"
#include "ILogDispatcher.h"
#include "VQLogger.h"
#include "LogStructures.h"

namespace Vam { namespace Logger {

class VQ_CORE_EXPORT LogLineHolder
{
public:
    LogLineHolder( LogMessage *msg )
        : m_msg( msg )
        , m_stream( &m_msg->mutableMessage() )
    {

    }

    QTextStream & stream()
    {
        return m_stream;
    }

    ~LogLineHolder()
    {
        m_stream.flush();
        VQLogger::get()->log( m_msg );
    }

private:
    LogMessage *m_msg;

    QTextStream m_stream;
};


} } // namespace Tanyatu

#define VQ_LOGGER() Vam::Logger::VQLogger::get()

#ifndef __FUNCTION_NAME__
    #ifdef _MSC_VER //VC++
        #define FUNCTION_NAME  __FUNCSIG__
    #else          //Other
        #define FUNCTION_NAME   __PRETTY_FUNCTION__
    #endif
#endif


#ifndef VQ_DISABLE_LOGGING
    #define VQ_LOG_COMMON( level, mod )                               \
        Vam::Logger::LogLineHolder(                                   \
           new Vam::Logger::LogMessage( QDateTime::currentDateTime(), \
                                        level,                        \
                                        CUR_THREAD_ID,                \
                                        mod,                          \
                                        FUNCTION_NAME,                \
                                        __LINE__,                     \
                                        QString( "" ))).stream()



    #define VQ_TRACE( module ) \
        VQ_LOG_COMMON( Vam::Logger::VQLogLevel::Trace, module )

    #define VQ_DEBUG( module ) \
        VQ_LOG_COMMON( Vam::Logger::VQLogLevel::Debug, module )

    #define VQ_INFO( module ) \
        VQ_LOG_COMMON( Vam::Logger::VQLogLevel::Info, module )

    #define VQ_WARN( module ) \
        VQ_LOG_COMMON( Vam::Logger::VQLogLevel::Warn, module )

    #define VQ_ERROR( module ) \
        VQ_LOG_COMMON( Vam::Logger::VQLogLevel::Error, module )

    #define VQ_FATAL( module ) \
        VQ_LOG_COMMON( Vam::Logger::VQLogLevel::Fatal, module )

    #define VQ_SPECIAL( module ) \
        VQ_LOG_COMMON( Vam::Logger::VQLogLevel::Special, module )
#else
    #define VQ_LOG_COMMON( level, mod, message )
    #define VQ_TRACE( module, message )
    #define VQ_DEBUG( module, message )
    #define VQ_INFO( module, message )
    #define VQ_WARNING( module, message )
    #define VQ_ERROR( module, message )
    #define VQ_FATAL( module, message )
#endif
