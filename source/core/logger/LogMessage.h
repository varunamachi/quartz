#pragma once

#include <cstdint>
#include <memory>


class QString;
class QDateTime;

namespace Quartz { namespace Logger {

enum class LogLevel : int;

class LogMessage
{
public:
    LogMessage( QDateTime &&time,
                LogLevel level,
                std::uint64_t threadId,
                const QString &module,
                QString &&method,
                int lineNum,
                const QString &message );

    LogMessage( QDateTime &&time,
                LogLevel level,
                std::uint64_t threadId,
                const QString &module,
                QString &&method,
                int lineNum,
                QString &&message );

    LogMessage( QDateTime &&time,
                LogLevel level,
                std::uint64_t threadId,
                QString &&module,
                QString &&method,
                int lineNum,
                QString &&message );

    const LogLevel & logLevel() const;

    const QDateTime & time() const;

    const std::uint64_t & threadId() const;

    const QString & moduleName() const;

    const QString & methodName() const;

    const int & lineNum() const;

    const QString & message() const;

    QString & message();

    void setMessage( const QString &message );

    void setMessage( QString &&message );

    ~LogMessage();

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;
};

} }
