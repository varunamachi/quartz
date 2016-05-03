#pragma once

#include "../VQCommon.h"

class QString;

namespace Vam { namespace Logger {

class LogMessage;

VQ_INTERFACE ILogFormatter
{
    virtual QString format( const LogMessage *message ) = 0;

    virtual ~ILogFormatter() { }
};


} }
