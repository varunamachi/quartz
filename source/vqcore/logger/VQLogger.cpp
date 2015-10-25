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

namespace Vam { namespace Logger {

VQLogger *VQLogger::s_instance = 0;


bool VQLogger::init( ILogDispatcher *dispatcher, VQLogLevel level )
{
    bool result = false;
    if( s_instance == nullptr ) {
        s_instance = new VQLogger( dispatcher, level );
        result = true;
    }
    return result;
}


void VQLogger::destroy()
{
    delete s_instance;
}


void VQLogger::log( QDateTime &time,
                    VQLogLevel level,
                    int lineNumber,
                    QString &module,
                    QString &method,
                    QString &message )
{
    if( m_enabled
        && m_dispatcher != nullptr
        && level >= m_globalSevLevel ) {
        LogMessage *lgmsg = new LogMessage( level,
                                            time,
                                            CUR_THREAD_ID,
                                            module,
                                            method,
                                            lineNumber,
                                            message );
        m_dispatcher->write( lgmsg );
    }

}


void VQLogger::log( LogMessage *msg )
{
    if( m_enabled
        && m_dispatcher != nullptr
        && msg->logLevel() >= m_globalSevLevel ) {
        m_dispatcher->write( msg );
    }
}

} } // end of namespaces
