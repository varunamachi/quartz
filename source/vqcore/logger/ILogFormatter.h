#pragma once

#include "../VQCommon.h"

class std::string;

namespace Vam { namespace Logger {

class LogMessage;

VQ_INTERFACE ILogFormatter
{
    virtual std::string format( const LogMessage *message ) = 0;

    virtual ~ILogFormatter() { }
};


} }
