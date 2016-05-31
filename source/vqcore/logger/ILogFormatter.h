#pragma once

#include "../VQCommon.h"



namespace Vq { namespace Logger {

class LogMessage;

VQ_INTERFACE ILogFormatter
{
    virtual std::string format( const LogMessage *message ) = 0;

    virtual ~ILogFormatter() { }
};


} }
