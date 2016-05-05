#pragma once

#include <memory>

#include "../VQ.h"
#include "../VQCommon.h"


#define CUR_THREAD_ID quint64( 0 )

class QString;
class QDateTime;

namespace Vam { namespace Logger {

VQ_INTERFACE ILogDispatcher;
class LogMessage;
enum class VQLogLevel : int;


class VQ_CORE_EXPORT VQLogger final
{
public:

    void setDispatcher( std::unique_ptr< ILogDispatcher > &&dispatcher );

    ILogDispatcher * dispatcher() const;

    void setFilterLevel( VQLogLevel level );

    bool isMethodLoggingEnabled() const;

    void setMethodLogState( bool value );

    VQLogLevel filterLevel() const;

    bool isEnabled() const;

    void setEnabled( bool val );

//    void log( const QDateTime &time,
//              VQLogLevel &level,
//              const QString &module,
//              const QString &&method,
//              int lineNum,
//              const QString &message );

//    void log( const QDateTime &time,
//              VQLogLevel &level,
//              const QString &module,
//              const QString &&method,
//              int lineNum,
//              QString &&message );

//    void log( const QDateTime &time,
//              VQLogLevel &level,
//              const QString &&module,
//              const QString &&method,
//              int lineNum,
//              QString &&message );

    void log( LogMessage *msg );

    VQLogger( std::unique_ptr< ILogDispatcher > dispatcher, VQLogLevel level );

    static VQLogger * get();

    static bool init( std::unique_ptr< ILogDispatcher > &&dispatcher,
                      VQLogLevel level );

    static void destroy();

private:

    class Impl;
    std::unique_ptr< Impl > m_impl;

    static std::unique_ptr< VQLogger > s_instance;
};

} }


