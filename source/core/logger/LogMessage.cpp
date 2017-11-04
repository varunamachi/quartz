#include <QString>
#include <QDateTime>

#include "LogMessage.h"

namespace Quartz { namespace Logger {

class LogMessage::Data
{
public:
    Data( QDateTime &&time,
          LogLevel &level,
          std::uint64_t threadId,
          const QString &module,
          QString &&method,
          QString &&fileName,
          int lineNum,
          const QString &message )
        : m_time{ time }
        , m_logLevel{ level }
        , m_threadId{ threadId }
        , m_moduleName{ module }
        , m_methodName{ std::move( method )}
        , m_fileName{ fileName }
        , m_lineNumber{ lineNum }
        , m_logMessage{ message }
    {

    }


    Data( QDateTime &&time,
          LogLevel &level,
          std::uint64_t threadId,
          const QString &module,
          QString &&method,
          QString &&fileName,
          int lineNum,
          QString &&message )
        : m_time{ std::move( time )}
        , m_logLevel{ level }
        , m_threadId{ threadId }
        , m_moduleName{ module }
        , m_methodName{ std::move( method )}
        , m_fileName{ fileName }
        , m_lineNumber{ lineNum }
        , m_logMessage{ std::move( message )}
    {

    }

    Data( QDateTime &&time,
          LogLevel &level,
          std::uint64_t threadId,
          QString &&module,
          QString &&method,
          QString &&fileName,
          int lineNum,
          QString &&message )
        : m_time{ std::move( time )}
        , m_logLevel{ level }
        , m_threadId{ threadId }
        , m_moduleName{ std::move( module )}
        , m_methodName{ std::move( method )}
        , m_fileName{ fileName }
        , m_lineNumber{ lineNum }
        , m_logMessage{ std::move( message )}
    {

    }

    QDateTime m_time;

    LogLevel m_logLevel;

    std::uint64_t m_threadId;

    QString m_moduleName;

    QString m_methodName;

    QString m_fileName;

    int m_lineNumber;

    QString m_logMessage;
};


LogMessage::LogMessage( QDateTime &&time,
                        LogLevel level,
                        std::uint64_t threadId,
                        const QString &module,
                        QString &&method,
                        QString &&fileName,
                        int lineNum,
                        const QString &message )
    : m_data( new Data{
                  std::move( time ),
                  level,
                  threadId,
                  module,
                  std::move( method ),
                  std::move( fileName ),
                  lineNum,
                  message })
{

}


LogMessage::LogMessage( QDateTime &&time,
                        LogLevel level,
                        std::uint64_t threadId,
                        const QString &module,
                        QString &&method,
                        QString &&fileName,
                        int lineNum,
                        QString &&message )
    : m_data( new Data{
                  std::move( time ),
                  level,
                  threadId,
                  module,
                  std::move( method ),
                  std::move( fileName ),
                  lineNum,
                  std::move( message )})
{

}



LogMessage::LogMessage( QDateTime &&time,
                        LogLevel level,
                        std::uint64_t threadId,
                        QString &&module,
                        QString &&method,
                        QString &&fileName,
                        int lineNum,
                        QString &&message )
    : m_data( new Data{
                  std::move( time ),
                  level,
                  threadId,
                  std::move( module ),
                  std::move( method ),
                  std::move( fileName ),
                  lineNum,
                  std::move( message ) })
{

}


const LogLevel & LogMessage::logLevel() const
{
    return m_data->m_logLevel;
}


const QDateTime & LogMessage::time() const
{
    return m_data->m_time;
}


const std::uint64_t & LogMessage::threadId() const
{
    return m_data->m_threadId;
}


const QString & LogMessage::moduleName() const
{
    return m_data->m_moduleName;
}


const QString & LogMessage::methodName() const
{
    return m_data->m_methodName;
}

const QString &LogMessage::fileName() const
{
    return m_data->m_fileName;
}


const int & LogMessage::lineNum() const
{
    return m_data->m_lineNumber;
}


const QString & LogMessage::message() const
{
    return m_data->m_logMessage;
}

QString & LogMessage::message()
{
    return m_data->m_logMessage;
}


void LogMessage::setMessage( const QString &message )
{
    m_data->m_logMessage = message;
}


void LogMessage::setMessage( QString &&message )
{
    m_data->m_logMessage = message;
}

LogMessage::~LogMessage()
{

}


} }
