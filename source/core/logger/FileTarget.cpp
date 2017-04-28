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
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>


#include "FileTarget.h"
#include "LogUtil.h"

namespace Quartz { namespace Logger {

class FileTarget::Impl
{
public:
    Impl( const QString &logDirPath,
          const QString &fileSuffix );

    void write( const QString &&message );

    void flush();

    static const QString TARGET_ID;

private:
    void initFile();

    std::unique_ptr< QFile > m_logFile;

    QString m_logDirPath;

    QString m_fileSuffix;

    QDateTime m_prevDate;

    QTextStream m_stream;

    bool m_valid;

};



FileTarget::Impl::Impl( const QString &logDirPath,
                        const QString &fileSuffix )
    : m_logDirPath{ logDirPath }
    , m_fileSuffix{ fileSuffix }
    , m_prevDate{ QDateTime::currentDateTime()  }
    , m_valid{ false }
{
    initFile();
}


void FileTarget::Impl::write( const QString &&message )
{
    if( m_prevDate.daysTo( QDateTime::currentDateTime() ) != 0 ) {
        m_stream.flush();
        initFile();
    }
    if( m_valid ) {
        m_stream << message << "\n";
    }
}


void FileTarget::Impl::flush()
{
    m_stream.flush();
}


void FileTarget::Impl::initFile()
{
    QString fileName = m_prevDate.toString( "yyyy_MM_dd_" )
                       + m_fileSuffix
                       + ".log";
    auto filePath = m_logDirPath + "/" + fileName;
    m_stream.reset();
    m_logFile = std::unique_ptr< QFile >{ new QFile{ filePath }};
    if( m_logFile->open( QIODevice::Append | QIODevice::Unbuffered )) {
        m_stream.setDevice( m_logFile.get() );
        m_valid = true;
    }
    else {
        qDebug() << "Could not open the file....";
        m_valid = false;
    }
}



//---------------- File Target -----------------------------
const QString FileTarget::TARGET_ID = QString( "FileLogger" );

FileTarget::FileTarget( const QString &logDirPath,
                        const QString &fileSuffix )
    : AbstractLogTarget( TARGET_ID )
    , m_impl{ new Impl{ logDirPath, fileSuffix }}
{

}

FileTarget::~FileTarget()
{

}


void FileTarget::write( QString &&message )
{
    m_impl->write( std::move( message ));
}

void FileTarget::flush()
{
    m_impl->flush();
}


} } //end of namespaces
