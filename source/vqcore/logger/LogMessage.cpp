#include <QString>
#include <QDateTime>

#include "LogMessage.h"

namespace Vam { namespace Logger {

class LogMessage::Impl
{
public:
    Impl( const QDateTime &time,
          VQLogLevel &level,
          std::uint64_t threadId,
          const QString &module,
          const QString &&method,
          int lineNum,
          const QString &message )
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
          const QString &module,
          const QString &&method,
          int lineNum,
          QString &&message )
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
          const QString &&module,
          const QString &&method,
          int lineNum,
          QString &&message )
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

    inline const QString & moduleName() const
    {
        return m_moduleName;
    }

    inline const QString & methodName() const
    {
        return m_methodName;
    }

    inline const int & lineNum() const
    {
        return m_lineNumber;
    }

    inline const QString & message() const
    {
        return m_logMessage;
    }

    inline QString & mutableMessage()
    {
        return m_logMessage;
    }

private:
    QDateTime m_time;

    VQLogLevel m_logLevel;

    std::uint64_t m_threadId;

    QString m_moduleName;

    QString m_methodName;

    int m_lineNumber;

    QString m_logMessage;
};


LogMessage::LogMessage( const QDateTime &&time,
                        VQLogLevel level,
                        std::uint64_t threadId,
                        const QString &module,
                        const QString &&method,
                        int lineNum,
                        const QString &message )
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
                        const QString &module,
                        const QString &&method,
                        int lineNum,
                        QString &&message )
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
                        const QString &&module,
                        const QString &&method,
                        int lineNum,
                        QString &&message )
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


const QString & LogMessage::moduleName() const
{
    return m_impl->moduleName();
}


const QString & LogMessage::methodName() const
{
    return m_impl->methodName();
}


const int & LogMessage::lineNum() const
{
    return m_impl->lineNum();
}


const QString & LogMessage::message() const
{
    return m_impl->message();
}


QString & LogMessage::mutableMessage() const
{
    return m_impl->mutableMessage();
}

LogMessage::~LogMessage()
{

}


} }
