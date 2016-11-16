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

#include <QString>
#include <QDateTime>

#include "LogUtil.h"
#include "LogStructures.h"
#include "LogMessage.h"


namespace Quartz { namespace Logger {



QString LogUtil::getSeverityString( LogLevel level )
{
    switch( level ) {
    case LogLevel::Trace  : return "[ TRACE ]";
    case LogLevel::Debug  : return "[ DEBUG ]";
    case LogLevel::Info   : return "[ INFO  ]";
    case LogLevel::Warn   : return "[ WARNG ]";
    case LogLevel::Error  : return "[ ERROR ]";
    case LogLevel::Fatal  : return "[ FATAL ]";
    case LogLevel::Special: return "[ ***** ]";
    case LogLevel::Method : return "[ ***** ]";
    }
    return "";
}


QString LogUtil::format( const LogMessage *msg )
{
    QString strMsg{ msg->time().toString( "yyyy-MM-dd hh:mm:ss" )
            + " "
            + getSeverityString( msg->logLevel() )
            + "  "
            + msg->message()
  /*          + " ["
            + msg->moduleName() + " | "
            + QString::number( msg->lineNum()  ) + " | "
            + QString::number( msg->threadId() ) + " | "
            + msg->methodName() + " ] "*/
    };
    return strMsg;
}

} } //end of namespces
