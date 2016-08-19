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

#include "LogUtil.h"
#include "Logger.h"

namespace Quartz {



QString LogUtil::getSeverityString( TntLogLevel level )
{
    switch( level ) {
    case TntLogLevel::Trace : return "[ TRACE ]";
    case TntLogLevel::Debug : return "[ DEBUG ]";
    case TntLogLevel::Info  : return "[ INFO  ]";
    case TntLogLevel::Warn  : return "[ WARNG ]";
    case TntLogLevel::Error : return "[ ERROR ]";
    case TntLogLevel::Fatal : return "[ FATAL ]";
    case TntLogLevel::Method:
    case TntLogLevel::Special: return "[ ***** ]";
    }
    return "[ ***** ]";
}


QString LogUtil::format( const LogMessage *msg )
{
    QString strMsg = QString( msg->time().toString( "yyyy-MM-dd hh:mm:ss" ))
            + " "
            + getSeverityString( msg->logLevel() )
            + "  "
            + msg->message()
  /*          + " ["
            + msg->moduleName() + " | "
            + QString::number( msg->lineNum()  ) + " | "
            + QString::number( msg->threadId() ) + " | "
            + msg->methodName() + " ] "*/;
    return strMsg;
}

} //end of namespces
