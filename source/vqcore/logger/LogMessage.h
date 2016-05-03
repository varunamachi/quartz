#pragma once

#include <cstdint>
#include <memory>

class QString;
class QDateTime;


namespace Vam { namespace Logger {

enum class VQLogLevel : int;

struct LogMessage
{
public:
    LogMessage( VQLogLevel &level,
                const QDateTime &time,
                std::uint64_t threadId,
                const QString &module,
                const QString &&method,
                int lineNum,
                QString &message );

    LogMessage( VQLogLevel &level,
                const QDateTime &time,
                std::uint64_t threadId,
                const QString &module,
                const QString &&method,
                int lineNum,
                QString &&message );

    LogMessage( VQLogLevel &level,
                const QDateTime &time,
                std::uint64_t threadId,
                const QString &&module,
                const QString &&method,
                int lineNum,
                QString &&message );

    const VQLogLevel & logLevel() const;

    const QDateTime & time() const;

    const std::uint32_t & threadId() const;

    const QString & moduleName() const;

    const QString & methodName() const;

    const int & lineNum() const;

    const QString & message() const;

    QString & mutableMessage() const;

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;
};

} }
