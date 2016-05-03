#pragma once

#include "../VQCommon.h"

class QString;

namespace Vam { namespace Logger {

class AbstractLogTarget;
class LogMessage;
class ILogFilter;

VQ_INTERFACE ILogDispatcher
{
    virtual bool addTarget( AbstractLogTarget *target ) = 0;

    virtual AbstractLogTarget * target( QString targetId ) = 0;

    virtual bool setTargetEnabledState( const QString &trgId, bool value ) = 0;

    virtual bool removeTarget( const QString &trgId ) = 0;

    virtual bool installFilter( ILogFilter *filter,
                                const QString &trgId ) = 0;

    virtual bool uninstallFilter( const QString &filterId,
                                  const QString &trgId ) = 0;

    virtual void write( LogMessage *message ) = 0;

    virtual void flush() = 0;

    virtual void stopDispatch() = 0;

    inline virtual ~ILogDispatcher(){ }
};


} }
