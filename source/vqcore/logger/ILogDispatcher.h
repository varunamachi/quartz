#pragma once

#include <memory>

#include "../VQCommon.h"



namespace Vam { namespace Logger {

class AbstractLogTarget;
class LogMessage;
VQ_INTERFACE ILogFilter;

VQ_INTERFACE ILogDispatcher
{
    virtual bool addTarget( std::unique_ptr< AbstractLogTarget > &&target ) = 0;

    virtual AbstractLogTarget * target( std::string targetId ) = 0;

    virtual bool setTargetEnabledState( const std::string &trgId, bool value ) = 0;

    virtual bool removeTarget( const std::string &trgId ) = 0;

    virtual bool installFilter( std::shared_ptr< ILogFilter > filter,
                                const std::string &trgId ) = 0;

    virtual bool uninstallFilter( const std::string &filterId,
                                  const std::string &trgId ) = 0;

    virtual void write( LogMessage *message ) = 0;

    virtual void flush() = 0;

    virtual void stopDispatch() = 0;

    inline virtual ~ILogDispatcher(){ }
};


} }
