#pragma once

#include "../VQCommon.h"

namespace Vam { namespace Logger {

class LogMessage;
class QString;

VQ_INTERFACE ILogFilter
{
    virtual QString filterId() const = 0;

    virtual bool filterOut( LogMessage *message ) = 0;

    inline virtual ~ILogFilter(){ }
};


} }
