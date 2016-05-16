#include <std::string>
#include <QDateTime>

#include "LogMessage.h"

namespace Vam { namespace Logger {

class LogMessage::Impl
{
public:
    Impl( const QDateTime &time,
          VQLogLevel &level,
          std::uint64_t threadId,
          const std::string &module,
          const std::string &&method,
          int lineNum,
          const std::string &message )
        : m_time( time )
        , m_logLevel( level )
        , m_threadId( threadId )
        , m_moduleName( module )
        , m_methodName( std::move( method ))
        , m_lineNumber( lineNum )
        , m_logMessage( message )
    {

    }


    Impl( const QDateTime &time,
          VQLogLevel &level,
          std::uint64_t threadId,
          const std::string &module,
          const std::string &&method,
          int lineNum,
          std::string &&message )
        : m_time( time )
        , m_logLevel( level )
        , m_threadId( threadId )
        , m_moduleName( module )
        , m_methodName( std::move( method ))
        , m_lineNumber( lineNum )
        , m_logMessage( std::move( message ))
    {

    }

    Impl( const QDateTime &time,
          VQLogLevel &level,
          std::uint64_t threadId,
          const std::string &&module,
          const std::string &&method,
          int lineNum,
          std::string &&message )
        : m_time( time )
        , m_logLevel( level )
        , m_threadId( threadId )
        , m_moduleName( std::move( module ))
        , m_methodName( std::move( method ))
        , m_lineNumber( lineNum )
        , m_logMessage( std::move( message ))
    {

    }


    inline const VQLogLevel & logLevel() const
    {
        return m_logLevel;
    }

    inline const QDateTime & time() const
    {
        return m_time;
    }

    inline const std::uint64_t & threadId() const
    {
        return m_threadId;
    }

    inline const std::string & moduleName() const
    {
        return m_moduleName;
    }

    inline const std::string & methodName() const
    {
        return m_methodName;
    }

    inline const int & lineNum() const
    {
        return m_lineNumber;
    }

    inline const std::string & message() const
    {
        return m_logMessage;
    }

    inline std::string & mutableMessage()
    {
        return m_logMessage;
    }

private:
    QDateTime m_time;

    VQLogLevel m_logLevel;

    std::uint64_t m_threadId;

    std::string m_moduleName;

    std::string m_methodName;

    int m_lineNumber;

    std::string m_logMessage;
};


LogMessage::LogMessage( const QDateTime &&time,
                        VQLogLevel level,
                        std::uint64_t threadId,
                        const std::string &module,
                        const std::string &&method,
                        int lineNum,
                        const std::string &message )
    : m_impl( std::make_unique< LogMessage::Impl >(
                  std::move( time ),
                  level,
                  threadId,
                  module,
                  std::move( method ),
                  lineNum,
                  message ))
{

}


LogMessage::LogMessage( const QDateTime &&time,
                        VQLogLevel level,
                        std::uint64_t threadId,
                        const std::string &module,
                        const std::string &&method,
                        int lineNum,
                        std::string &&message )
    : m_impl( std::make_unique< LogMessage::Impl >(
                  std::move( time ),
                  level,
                  threadId,
                  module,
                  std::move( method ),
                  lineNum,
                  std::move( message ) ))
{

}



LogMessage::LogMessage( const QDateTime &&time,
                        VQLogLevel level,
                        std::uint64_t threadId,
                        const std::string &&module,
                        const std::string &&method,
                        int lineNum,
                        std::string &&message )
    : m_impl( std::make_unique< LogMessage::Impl >(
                  std::move( time ),
                  level,
                  threadId,
                  std::move( module ),
                  std::move( method ),
                  lineNum,
                  std::move( message ) ))
{

}


const VQLogLevel & LogMessage::logLevel() const
{
    return m_impl->logLevel();
}


const QDateTime & LogMessage::time() const
{
    return m_impl->time();
}


const std::uint64_t & LogMessage::threadId() const
{
    return m_impl->threadId();
}


const std::string & LogMessage::moduleName() const
{
    return m_impl->moduleName();
}


const std::string & LogMessage::methodName() const
{
    return m_impl->methodName();
}


const int & LogMessage::lineNum() const
{
    return m_impl->lineNum();
}


const std::string & LogMessage::message() const
{
    return m_impl->message();
}


std::string & LogMessage::mutableMessage() const
{
    return m_impl->mutableMessage();
}

LogMessage::~LogMessage()
{

}


} }
