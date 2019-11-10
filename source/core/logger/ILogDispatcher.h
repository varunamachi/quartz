#pragma once

#include <memory>

#include "../utils/Macros.h"

class QString;

namespace Quartz { namespace Logger {

class AbstractLogTarget;
class LogMessage;
QZ_INTERFACE ILogFilter;

QZ_INTERFACE ILogDispatcher {
    virtual bool addTarget(std::unique_ptr<AbstractLogTarget> && target) = 0;

    virtual AbstractLogTarget* target(QString targetId) = 0;

    virtual bool setTargetEnabledState(const QString& trgId, bool value) = 0;

    virtual bool removeTarget(const QString& trgId) = 0;

    virtual bool installFilter(std::shared_ptr<ILogFilter> filter,
                               const QString& trgId)
        = 0;

    virtual bool uninstallFilter(const QString& filterId, const QString& trgId)
        = 0;

    virtual void write(LogMessage * message) = 0;

    virtual void flush() = 0;

    virtual void stopDispatch() = 0;

    inline virtual ~ILogDispatcher() {
    }
};

}} // namespace Quartz::Logger
