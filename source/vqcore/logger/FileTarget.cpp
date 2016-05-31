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
#include <QDebug>
#include <QTextStream>
#include <QPointer>
#include <QFile>
#include <QDateTime>

#include "FileTarget.h"
#include "LogUtil.h"

namespace Vq { namespace Logger {

class FileTarget::Impl
{
public:
    Impl( const std::string &fileSuffix );

    void write( const std::string &&message );

    void flush();

    static const std::string TARGET_ID;

private:
    void initFile();

    QPointer< QFile > m_logFile;

    std::string m_fileSuffix;

    QDateTime m_prevDate;

    QTextStream m_stream;

};



FileTarget::Impl::Impl( const std::string &fileSuffix )
    : m_fileSuffix( fileSuffix )
    , m_prevDate( QDateTime::currentDateTime() )
{
    initFile();
}


void FileTarget::Impl::write( const std::string &&message )
{
    if( m_prevDate.daysTo( QDateTime::currentDateTime() ) != 0 ) {
        m_stream.flush();
        initFile();
    }
    m_stream << message << endl;
}


void FileTarget::Impl::flush()
{
    m_stream.flush();
}


void FileTarget::Impl::initFile()
{
    std::string fileName = m_prevDate.toString( "yyyy_MM_dd_" )
                       + m_fileSuffix
                       + ".log";
    m_stream.reset();
    m_logFile.clear();
    m_logFile = new QFile( fileName );
    if( m_logFile->open( QIODevice::Append | QIODevice::Unbuffered )) {
        m_stream.setDevice( m_logFile.data() );
    }
    else {
        qDebug() << "Could not open the file....";
    }
}



//---------------- File Target -----------------------------
const std::string FileTarget::TARGET_ID = std::string( "FileLogger" );

FileTarget::FileTarget( const std::string &fileSuffix )
    : AbstractLogTarget( TARGET_ID )
    , m_impl( std::make_unique< Impl >( fileSuffix ))
{

}


void FileTarget::write( const std::string &&message )
{
    m_impl->write( std::move( message ));
}

void FileTarget::flush()
{
    m_impl->flush();
}


} } //end of namespaces
