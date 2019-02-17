#pragma once

#include <QDateTime>
#include <QTextStream>

#include "LogStructures.h"
#include "LogMessage.h"
#include "ILogDispatcher.h"
#include "Logger.h"


namespace Quartz { namespace Logger {

struct _Str{};

constexpr _Str Str;

class QUARTZ_CORE_API LogLineHolder
{
public:
    typedef QTextStream & (Manip)(QTextStream &);

    LogLineHolder(Logger *logger, LogMessage *msg)
        : m_msg(msg)
        , m_logger(logger)
        , m_stream(&msg->message())
        , m_level(Logger::get()->filterLevel())
    {

    }

    template< typename T >
    LogLineHolder & operator<<(const T &obj)
    {
        if (m_msg->logLevel() >= m_level) {
            m_stream << obj;
        }
        return *this;
    }

    template< typename T >
    LogLineHolder & operator<<(T &&obj)
    {
        if (m_msg->logLevel() >= m_level) {
            m_stream << obj;
        }
        return *this;
    }

    LogLineHolder & operator << (Manip &manip)
    {
        if (m_msg->logLevel() >= m_level) {
            m_stream << manip;
        }
        return *this;
    }

    const QString & operator << (const _Str &)
    {
        return m_msg->message();
    }

    ~LogLineHolder()
    {
        if (m_msg->logLevel() >= m_level) {
            m_stream.flush();
            if (m_logger != nullptr) {
                m_logger->log(m_msg);
            }
        }
    }

private:
    LogMessage *m_msg;

    Logger *m_logger;

    QTextStream m_stream;

    LogLevel m_level;
};


} } // namespace Tanyatu

#define QZ_LOGGER() Quartz::Logger::Logger::get()

#ifndef __FUNCTION_NAME__
    #ifdef _MSC_VER //VC++
        #define FUNCTION_NAME  __FUNCSIG__
    #else          //Other
        #define FUNCTION_NAME   __PRETTY_FUNCTION__
    #endif
#endif


#ifndef QZ_DISABLE_DEFAULT_LOGGING
        #define QZ_COMMON(level, mod)                                       \
            Quartz::Logger::LogLineHolder(                                  \
                Quartz::Logger::Logger::get(),                                \
                new Quartz::Logger::LogMessage{ QDateTime::currentDateTime(), \
                                                level,                        \
                                                CUR_THREAD_ID,                \
                                                mod,                          \
                                                FUNCTION_NAME,                \
                                                __FILE__,                     \
                                                __LINE__,                     \
                                                QString("")})
        #define QZ_TRACE(module) \
            QZ_COMMON(Quartz::Logger::LogLevel::Trace, module)

        #define QZ_DEBUG(module) \
            QZ_COMMON(Quartz::Logger::LogLevel::Debug, module)

        #define QZ_INFO(module) \
            QZ_COMMON(Quartz::Logger::LogLevel::Info, module)

        #define QZ_WARN(module) \
            QZ_COMMON(Quartz::Logger::LogLevel::Warn, module)

        #define QZ_ERROR(module) \
            QZ_COMMON(Quartz::Logger::LogLevel::Error, module)

        #define QZ_FATAL(module) \
            QZ_COMMON(Quartz::Logger::LogLevel::Fatal, module)

        #define QZ_SPECIAL(module) \
            QZ_COMMON(Quartz::Logger::LogLevel::Special, module)
#else
    #define QZ_COMMON(level, mod, message)
    #define QZ_TRACE(module)
    #define QZ_DEBUG(module)
    #define QZ_INFO(module)
    #define QZ_WARNING(module)
    #define QZ_ERROR(module)
    #define QZ_FATAL(module)
    #define QZ_SPECIAL(module)
#endif
