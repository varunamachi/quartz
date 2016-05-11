/*******************************************************************************
 * Copyright (c) 2014 Varuna L Amachi. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 ******************************************************************************/

#include "VQLogger.h"
#include "ILogDispatcher.h"
#include "LogStructures.h"
#include "LogMessage.h"


namespace Vam { namespace Logger {

VQ_INTERFACE ILogDispatcher;


class VQLogger::Impl
{
public:

    inline void setDispatcher( std::unique_ptr< ILogDispatcher > &&dispatcher )
    {
        m_dispatcher = std::move( dispatcher );
    }

    inline ILogDispatcher * dispatcher() const
    {
        return m_dispatcher.get();
    }

    inline void setFilterLevel( VQLogLevel level )
    {
        m_globalSevLevel = level;
    }

    inline bool isMethodLoggingEnabled() const
    {
        return m_logMethods;
    }

    inline void setMethodLogState( bool value )
    {
        m_logMethods = value;
    }

    inline VQLogLevel filterLevel() const
    {
        return m_globalSevLevel;
    }

    inline bool isEnabled() const
    {
        return m_enabled;
    }

    inline void setEnabled( bool val )
    {
        m_enabled = val;
    }

//    void log(const QDateTime &time,
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

    Impl( std::unique_ptr< ILogDispatcher > dispatcher, VQLogLevel level )
        : m_dispatcher( std::move( dispatcher ))
        , m_globalSevLevel( level )
        , m_logMethods( false )
        , m_enabled( true )
    {

    }
private:
    std::unique_ptr< ILogDispatcher > m_dispatcher;

    VQLogLevel m_globalSevLevel;

    bool m_logMethods;

    bool m_enabled;

};

//void VQLogger::Impl::log( const QDateTime &time,
//          VQLogLevel &level,
//          const QString &module,
//          const QString &&method,
//          int lineNum,
//          const QString &message )
//{
//    if( m_enabled
//        && m_dispatcher != nullptr
//        && level >= m_globalSevLevel ) {
//        LogMessage *lgmsg = new LogMessage( time,
//                                            level,
//                                            CUR_THREAD_ID,
//                                            module,
//                                            std::move( method ),
//                                            lineNum,
//                                            message );
//        m_dispatcher->write( lgmsg );
//    }
//}

//void VQLogger::Impl::log( const QDateTime &time,
//          VQLogLevel &level,
//          const QString &module,
//          const QString &&method,
//          int lineNum,
//          QString &&message )
//{
//    if( m_enabled
//        && m_dispatcher != nullptr
//        && level >= m_globalSevLevel ) {
//        LogMessage *lgmsg = new LogMessage( time,
//                                            level,
//                                            CUR_THREAD_ID,
//                                            module,
//                                            std::move( method ),
//                                            lineNum,
//                                            std::move( message ));
//        m_dispatcher->write( lgmsg );
//    }
//}

//void VQLogger::Impl::log( const QDateTime &time,
//          VQLogLevel &level,
//          const QString &&module,
//          const QString &&method,
//          int lineNum,
//          QString &&message )
//{
//    if( m_enabled
//        && m_dispatcher != nullptr
//        && level >= m_globalSevLevel ) {
//        LogMessage *lgmsg = new LogMessage( time,
//                                            level,
//                                            CUR_THREAD_ID,
//                                            std::move( module ),
//                                            std::move( method ),
//                                            lineNum,
//                                            std::move( message ));
//        m_dispatcher->write( lgmsg );
//    }
//}

void VQLogger::Impl::log( LogMessage *msg )
{
    if( m_enabled
        && m_dispatcher != nullptr
        && msg->logLevel() >= m_globalSevLevel ) {
        m_dispatcher->write( msg );
    }
}


//=================================VQLogger ===================================

std::unique_ptr< VQLogger > VQLogger::s_instance = nullptr;


bool VQLogger::init( std::unique_ptr < ILogDispatcher > &&dispatcher,
                     VQLogLevel level )
{
    bool result = false;
    if( s_instance == nullptr ) {
        s_instance = std::make_unique< VQLogger >( std::move( dispatcher ),
                                                   level );
        result = true;
    }
    return result;
}


void VQLogger::destroy()
{

}


void VQLogger::log( LogMessage *msg )
{
    m_impl->log( msg );
}


VQLogger::VQLogger( std::unique_ptr< ILogDispatcher > dispatcher,
                    VQLogLevel level )
    : m_impl( std::make_unique< Impl >( std::move( dispatcher ), level ))
{

}


VQLogger * VQLogger::get()
{
    return s_instance.get();
}

} } // end of namespaces
