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
    Impl( const QString &fileSuffix );

    void write( const QString &&message );

    void flush();

    static const QString TARGET_ID;

private:
    void initFile();

    std::unique_ptr< QFile > m_logFile;

    QString m_fileSuffix;

    QDateTime m_prevDate;

    QTextStream m_stream;

};



FileTarget::Impl::Impl( const QString &fileSuffix )
    : m_fileSuffix( fileSuffix )
    , m_prevDate( QDateTime::currentDateTime()  )
{
    initFile();
}


void FileTarget::Impl::write( const QString &&message )
{
    if( m_prevDate.daysTo( QDateTime::currentDateTime() ) != 0 ) {
        m_stream.flush();
        initFile();
    }
    m_stream << message << "\n";
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
    m_stream.reset();
    m_logFile = std::unique_ptr< QFile >{ new QFile( fileName )};
    if( m_logFile->open( QIODevice::Append | QIODevice::Unbuffered )) {
        m_stream.setDevice( m_logFile.get() );
    }
    else {
        qDebug() << "Could not open the file....";
    }
}



//---------------- File Target -----------------------------
const QString FileTarget::TARGET_ID = QString( "FileLogger" );

FileTarget::FileTarget( const QString &fileSuffix )
    : AbstractLogTarget( TARGET_ID )
//    , m_impl( std::make_unique< Impl >( fileSuffix ))
    , m_impl( new Impl( fileSuffix ))
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
