#pragma once

#include <memory>

#include "../QuartzCore.h"

#include "../utils/Macros.h"

class QString;

namespace Quartz { namespace Logger {

QZ_INTERFACE ILogFormatter;
class LogMessage;

class QUARTZ_CORE_API AbstractLogTarget
{
public:
    explicit AbstractLogTarget( const QString &uniqueId );

    const QString & uniqueId() const;

    void setFormatterOwned( ILogFormatter *formatter );

    virtual void write( const LogMessage *message );

    virtual ~AbstractLogTarget();

    virtual void flush() = 0;

protected:
    virtual void write( QString &&logString ) = 0;

    ILogFormatter * formatter() const;

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;

};

} }
