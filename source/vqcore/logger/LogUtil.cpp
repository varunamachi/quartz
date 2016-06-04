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

#include <string>

#include "../common/DateTimeUtils.h"
#include "../common/DateTime.h"
#include "../common/Timestamp.h"

#include "LogUtil.h"
#include "LogStructures.h"
#include "LogMessage.h"


namespace Vq { namespace Logger {



std::string LogUtil::getSeverityString( VQLogLevel level )
{
    switch( level ) {
    case VQLogLevel::Trace  : return "[ TRACE ]";
    case VQLogLevel::Debug  : return "[ DEBUG ]";
    case VQLogLevel::Info   : return "[ INFO  ]";
    case VQLogLevel::Warn   : return "[ WARNG ]";
    case VQLogLevel::Error  : return "[ ERROR ]";
    case VQLogLevel::Fatal  : return "[ FATAL ]";
    case VQLogLevel::Special: return "[ ***** ]";
    case VQLogLevel::Method : return "[ ***** ]";
    }
    return "";
}


std::string LogUtil::format( const LogMessage *msg )
{
    std::string strMsg = DateTimeUtils::format( msg->time(),
                                                "yyyy-MM-dd hh:mm:ss" )
            + " "
            + getSeverityString( msg->logLevel() )
            + "  "
            + msg->message()
  /*          + " ["
            + msg->moduleName() + " | "
            + std::string::number( msg->lineNum()  ) + " | "
            + std::string::number( msg->threadId() ) + " | "
            + msg->methodName() + " ] "*/;
    return strMsg;
}

} } //end of namespces
