#pragma once

#include <QString>

#include "../utils/Macros.h"

namespace Quartz { namespace Logger {

class LogMessage;

QZ_INTERFACE ILogFilter
{
    virtual QString filterId() const = 0;

    virtual bool filterOut(LogMessage *message) = 0;

    virtual ~ILogFilter(){ }
};


} }
