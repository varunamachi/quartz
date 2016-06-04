#pragma once

#include <string>

#include "../common/Macros.h"

namespace Vq { namespace Logger {

class LogMessage;

VQ_INTERFACE ILogFilter
{
    virtual std::string filterId() const = 0;

    virtual bool filterOut( LogMessage *message ) = 0;

    virtual ~ILogFilter(){ }
};


} }
