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

#pragma once

#include <QString>
#include <QDateTime>
#include <QtGlobal>


namespace Vam { namespace Logger {

class VQLogger;
enum class VQLogLevel
{
    Method  = -1,
    Trace   = 0,
    Debug   = 1,
    Info    = 2,
    Warn    = 3,
    Error   = 4,
    Fatal   = 5,
    Special = 6
};


struct LogMessage
{
public:
    LogMessage( VQLogLevel level,
                QDateTime time,
                quint64 threadId,
                QString module,
                QString method,
                int lineNum,
                QString message = "" )
        : m_logLevel( level )
        , m_time( time )
        , m_threadId( threadId )
        , m_moduleName( module )
        , m_methodName( method )
        , m_lineNumber( lineNum )
        , m_logMessage( message )
    {

    }

    inline const VQLogLevel & logLevel() const { return m_logLevel; }

    inline const QDateTime & time() const { return m_time; }

    inline const quint64 & threadId() const { return m_threadId; }

    inline const QString & moduleName() const { return m_moduleName; }

    inline const QString & methodName() const { return m_methodName; }

    inline const int & lineNum() const { return m_lineNumber; }

    inline const QString & message() const { return m_logMessage; }

    inline QString & mutableMessage() { return m_logMessage; }

private:
    VQLogLevel m_logLevel;

    QDateTime m_time;

    quint64 m_threadId;

    QString m_moduleName;

    QString m_methodName;

    int m_lineNumber;

    QString m_logMessage;
};

} } //end of ns
