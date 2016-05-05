#pragma once

#include "../VQCommon.h"

class QString;

namespace Vam { namespace Logger {

class LogMessage;

VQ_INTERFACE ILogFilter
{
    virtual QString filterId() const = 0;

    virtual bool filterOut( LogMessage *message ) = 0;

    virtual ~ILogFilter(){ }
};


} }
