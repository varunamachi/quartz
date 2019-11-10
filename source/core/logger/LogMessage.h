#pragma once

#include <cstdint>
#include <memory>

#include "../QuartzCore.h"

class QString;
class QDateTime;

namespace Quartz { namespace Logger {

enum class LogLevel : int;

class QUARTZ_CORE_API LogMessage final {
public:
    LogMessage(QDateTime&& time,
               LogLevel level,
               std::uint64_t threadId,
               const QString& module,
               QString&& method,
               QString&& fileName,
               int lineNum,
               const QString& message);

    LogMessage(QDateTime&& time,
               LogLevel level,
               std::uint64_t threadId,
               const QString& module,
               QString&& method,
               QString&& fileName,
               int lineNum,
               QString&& message);

    LogMessage(QDateTime&& time,
               LogLevel level,
               std::uint64_t threadId,
               QString&& module,
               QString&& method,
               QString&& fileName,
               int lineNum,
               QString&& message);

    const LogLevel& logLevel() const;

    const QDateTime& time() const;

    const std::uint64_t& threadId() const;

    const QString& moduleName() const;

    const QString& methodName() const;

    const QString& fileName() const;

    const int& lineNum() const;

    const QString& message() const;

    QString& message();

    void setMessage(const QString& message);

    void setMessage(QString&& message);

    ~LogMessage();

private:
    class Data;
    std::unique_ptr<Data> m_data;
};

}} // namespace Quartz::Logger
