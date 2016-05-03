#pragma once

#include <QString>
#include <QDateTime>
#include <QTextStream>
#include <QThread>
#include <QtGlobal>

#include "LogUtil.h"
#include "LogStructures.h"
#include "../VQ.h"


#define CUR_THREAD_ID quint64( 0 )

namespace Vam { namespace Logger {

class VQLogger;

VQ_INTERFACE ILogFormatter
{
    virtual QString format( const LogMessage *message ) = 0;

    virtual ~ILogFormatter() { }
};




class VQ_CORE_EXPORT VQLogger
{
public:

    void setDispatcher( ILogDispatcher *dispatcher )
    {
        if( m_dispatcher ) {
            delete m_dispatcher;
        }
        m_dispatcher = dispatcher;
    }

    ILogDispatcher * dispatcher() const
    {
        return m_dispatcher;
    }

    void setFilterLevel( VQLogLevel level )
    {
        m_globalSevLevel = level;
    }

    bool isMethodLoggingEnabled() const
    {
        return m_logMethods;
    }

    void setMethodLogState( bool value )
    {
        m_logMethods = value;
    }

    VQLogLevel filterLevel() const
    {
        return m_globalSevLevel;
    }

    static VQLogger * get()
    {
        return s_instance;
    }

    bool isEnabled() const
    {
        return m_enabled;
    }

    void setEnabled( bool val )
    {
        m_enabled = val;
    }

    void log( QDateTime &time,
              VQLogLevel level,
              int lineNumber,
              QString &module,
              QString &method,
              QString &message );

    void log( LogMessage *msg );

    static bool init( ILogDispatcher *dispatcher,
               VQLogLevel level = VQLogLevel::Info );

    static void destroy();

private:
    VQLogger( ILogDispatcher *dispatcher, VQLogLevel level )
        : m_dispatcher( dispatcher )
        , m_globalSevLevel( level )
        , m_logMethods( false )
        , m_enabled( true )
    {

    }


    ~VQLogger()
    {
        delete m_dispatcher;
    }

    static VQLogger *s_instance;

    ILogDispatcher *m_dispatcher;

    VQLogLevel m_globalSevLevel;

    bool m_logMethods;

    bool m_enabled;

};


class LogLineHolder
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
        #define __FUNCTION_NAME__   __FUNCSIG__
    #else          //Other
        #define __FUNCTION_NAME__   __PRETTY_FUNCTION__
    #endif
#endif


#ifndef VQ_DISABLE_LOGGING
    #define VQ_LOG_COMMON( level, mod )                                 \
        Vam::Logger::LogLineHolder(                                   \
           new Vam::Logger::LogMessage( level,                        \
                                        QDateTime::currentDateTime(), \
                                        CUR_THREAD_ID,                \
                                        mod,                          \
                                        __FUNCTION_NAME__,            \
                                        __LINE__ )).stream()



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
#else
    #define VQ_LOG_COMMON( level, mod, message )
    #define VQ_TRACE( module, message )
    #define VQ_DEBUG( module, message )
    #define VQ_INFO( module, message )
    #define VQ_WARNING( module, message )
    #define VQ_ERROR( module, message )
    #define VQ_FATAL( module, message )
#endif

