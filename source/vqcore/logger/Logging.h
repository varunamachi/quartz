#pragma once

#include <sstream>

#include "../common/Timestamp.h"
#include "LogMessage.h"
#include "ILogDispatcher.h"
#include "VqLogger.h"
#include "LogStructures.h"


namespace Vq { namespace Logger {

class VQ_API LogLineHolder
{
public:
    typedef std::ostream& ( Manip )( std::ostream& );

    LogLineHolder( LogMessage *msg )
        : m_msg( msg )
        , m_stream()
        , m_level( VqLogger::get()->filterLevel() )
    {

    }

    template< typename T >
    LogLineHolder & operator<<( const T &obj )
    {
        if( m_msg->logLevel() >= m_level ) {
            m_stream << obj;
        }
        return *this;
    }

    LogLineHolder& operator << ( Manip &manip )
    {
        if( m_msg->logLevel() >= m_level ) {
            m_stream << manip;
        }
        return *this;
    }

    ~LogLineHolder()
    {
        if( m_msg->logLevel() >= m_level ) {
            m_stream.flush();
            m_msg->setMessage( m_stream.str() );
            VqLogger::get()->log( m_msg );
        }
    }

private:
    LogMessage *m_msg;

    std::stringstream m_stream;

    VqLogLevel m_level;
};


} } // namespace Tanyatu

#define VQ_LOGGER() Vq::Logger::VQLogger::get()

#ifndef __FUNCTION_NAME__
    #ifdef _MSC_VER //VC++
        #define FUNCTION_NAME  __FUNCSIG__
    #else          //Other
        #define FUNCTION_NAME   __PRETTY_FUNCTION__
    #endif
#endif


#ifndef VQ_DISABLE_LOGGING
    #define VQ_LOG_COMMON( level, mod )                               \
        Vq::Logger::LogLineHolder(                                   \
           new Vq::Logger::LogMessage( Timestamp::now(), \
                                       level,                        \
                                       CUR_THREAD_ID,                \
                                       mod,                          \
                                       FUNCTION_NAME,                \
                                       __LINE__,                     \
                                       std::string( "" )))


    #define VQ_TRACE( module ) \
        VQ_LOG_COMMON( Vq::Logger::VqLogLevel::Trace, module )

    #define VQ_DEBUG( module ) \
        VQ_LOG_COMMON( Vq::Logger::VqLogLevel::Debug, module )

    #define VQ_INFO( module ) \
        VQ_LOG_COMMON( Vq::Logger::VqLogLevel::Info, module )

    #define VQ_WARN( module ) \
        VQ_LOG_COMMON( Vq::Logger::VqLogLevel::Warn, module )

    #define VQ_ERROR( module ) \
        VQ_LOG_COMMON( Vq::Logger::VqLogLevel::Error, module )

    #define VQ_FATAL( module ) \
        VQ_LOG_COMMON( Vq::Logger::VqLogLevel::Fatal, module )

    #define VQ_SPECIAL( module ) \
        VQ_LOG_COMMON( Vq::Logger::VqLogLevel::Special, module )
#else
    #define VQ_LOG_COMMON( level, mod, message )
    #define VQ_TRACE( module )
    #define VQ_DEBUG( module )
    #define VQ_INFO( module )
    #define VQ_WARNING( module )
    #define VQ_ERROR( module )
    #define VQ_FATAL( module )
    #define VQ_SPECIAL( module )
#endif
