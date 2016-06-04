#pragma once

#include <memory>
#include <string>
#include <cstdint>

#include "../Vq.h"
#include "../common/Macros.h"


#define CUR_THREAD_ID std::uint64_t( 0 )

class QDateTime;

namespace Vq { namespace Logger {

class AbstractLogDispatcher;
class LogMessage;
enum class VqLogLevel : int;


class VQ_API VqLogger final
{
public:

    void setDispatcher( std::unique_ptr< AbstractLogDispatcher > &&dispatcher );

    AbstractLogDispatcher * dispatcher() const;

    void setFilterLevel( VqLogLevel level );

    bool isMethodLoggingEnabled() const;

    void setMethodLogState( bool value );

    VqLogLevel filterLevel() const;

    bool isEnabled() const;

    void setEnabled( bool val );

    void log( LogMessage *msg );

    VqLogger( std::unique_ptr< AbstractLogDispatcher > dispatcher,
              VqLogLevel level );

    static VqLogger * get();

    static bool init( std::unique_ptr< AbstractLogDispatcher > &&dispatcher,
                      VqLogLevel level );

    static void destroy();

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;

    static std::unique_ptr< VqLogger > s_instance;
};



} }


