#pragma once

#include <memory>

#include "../VQCommon.h"



namespace Vq { namespace Logger {

VQ_INTERFACE ILogFormatter;
class LogMessage;

class AbstractLogTarget
{
public:
    explicit AbstractLogTarget( const std::string &uniqueId );

    const std::string & uniqueId() const;

    void setFormatterOwned( ILogFormatter *formatter );

    virtual void write( const LogMessage *message );

    virtual ~AbstractLogTarget();

    virtual void flush() = 0;

protected:
    virtual void write( const std::string &&logString ) = 0;

    ILogFormatter * formatter() const;

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;

};

} }
