#pragma once

#include <QString>

#include "../utils/Macros.h"



namespace Quartz { namespace Logger {

class LogMessage;

QZ_INTERFACE ILogFormatter
{
    virtual QString format( const LogMessage *message ) = 0;

    virtual ~ILogFormatter() { }
};


} }
