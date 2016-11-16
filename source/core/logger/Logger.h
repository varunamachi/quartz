#pragma once

#include <memory>
#include <QString>

#include "../QuartzCore.h"
#include "../utils/Macros.h"


#define CUR_THREAD_ID std::uint64_t( 0 )

class QDateTime;

namespace Quartz { namespace Logger {

class AbstractLogDispatcher;
class LogMessage;
enum class LogLevel : int;


class QUARTZ_CORE_API Logger final
{
public:
    void setDispatcher( std::unique_ptr< AbstractLogDispatcher > &&dispatcher );

    AbstractLogDispatcher * dispatcher() const;

    void setFilterLevel( LogLevel level );

    bool isMethodLoggingEnabled() const;

    void setMethodLogState( bool value );

    LogLevel filterLevel() const;

    bool isEnabled() const;

    void setEnabled( bool val );

    void log( LogMessage *msg );

    Logger( std::unique_ptr< AbstractLogDispatcher > dispatcher,
              LogLevel level );

    static Logger * get();

    static bool init( std::unique_ptr< AbstractLogDispatcher > &&dispatcher,
                      LogLevel level );

    static void destroy();

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;

    static std::unique_ptr< Logger > s_instance;
};



} }


