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
#include <QEvent>
#include <QCoreApplication>
#include <QDebug>

#include "JobManager.h"



namespace Tanyatu {

namespace {
class StdJob : public IJob
{
public:
    StdJob( QString name,
            JobFunc job,
            bool guiDispatch,
            QString category )
        : m_name( name )
        , m_jobFunc( job )
        , m_isGuiDispatch( guiDispatch )
        , m_category( category )
    {

    }

    const QString & name() const
    {
        return m_name;
    }

    const QString & category() const
    {
        return m_category;
    }

    bool shouldPostResponse() const
    {
        return m_isGuiDispatch;
    }

    RespFunc execute()
    {
        return m_jobFunc();
    }

private:
    QString m_name;

    JobFunc m_jobFunc;

    bool m_isGuiDispatch;

    QString m_category;
};


class CallbackEvent : public QEvent
{
public:
    CallbackEvent( RespFunc callback )
        : QEvent( CallbackEvent::type() )
        , m_callback( callback )
    {

    }

    void invokeCallback()
    {
        if( m_callback ) m_callback();
    }

    static QEvent::Type type()
    {
        QEvent::registerEventType( CallbackEvent::EVENT_TYPE );
        return CallbackEvent::EVENT_TYPE;
    }

    static const QEvent::Type EVENT_TYPE;

private:
    RespFunc m_callback;
};


} //end of anonymous namespace

const QEvent::Type CallbackEvent::EVENT_TYPE
                                          = static_cast< QEvent::Type >( 2334 );


JobManager::JobManager( QObject *parent )
    : QThread( parent )
{

}


bool JobManager::hasPendingJobs()
{
    SCOPE_LIMIT( m_lock.lockForRead(), m_lock.unlock() );
    return ! m_jobs.empty();
}



void JobManager::addJob( IJob *job )
{
    SCOPE_LIMIT( m_lock.lockForWrite(), m_lock.unlock() );
    m_jobs.append( job );
    if( ! this->isRunning() ) {
        this->start();
    }
    qDebug() << "Added Job: " << job->name();
}


void JobManager::addJob( QString name,
                         JobFunc job,
                         QString category,
                         bool postResponseToEventQueue )
{
    SCOPE_LIMIT( m_lock.lockForWrite(), m_lock.unlock() );
    m_jobs.append( new StdJob( name,
                               job,
                               postResponseToEventQueue,
                               category ));
    if( ! this->isRunning() ) {
        this->start();
    }
    qDebug() << "Added Job: " << name;
}


bool JobManager::cancelJob( QString name )
{
    SCOPE_LIMIT( m_lock.lockForWrite(), m_lock.unlock() );
    return m_cancelledJobs.insert( name ) != m_cancelledJobs.end();
}


bool JobManager::cancelJobCategory( QString category )
{
    SCOPE_LIMIT( m_lock.lockForWrite(), m_lock.unlock() );
    return m_cancelledCategories.insert( category )
                                                != m_cancelledCategories.end();
}


void JobManager::cancelAll()
{
    m_lock.lockForWrite();
    m_stopProcessing = true;
    m_lock.unlock();
    this->wait();
    SCOPE_LIMIT( m_lock.lockForWrite(), m_lock.unlock() );
    foreach( IJob *job, m_jobs ) {
        delete job;
    }
    m_cancelledCategories.clear();
    m_cancelledJobs.clear();
}


void JobManager::run()
{
    bool shouldExit = false;
    bool hasPendingTasks = true;
    IJob *job = nullptr;

    while( ! shouldExit ){
        m_lock.lockForRead();
        shouldExit = m_stopProcessing;
        hasPendingTasks = m_jobs.size() != 0;
        m_lock.unlock();
        if( hasPendingTasks ) {
            m_lock.lockForWrite();
            qDebug() << "Jobs_1: " <<  m_jobs.size();
            job = m_jobs.last();
            m_jobs.removeLast();
            bool isCancelled = m_cancelledJobs.remove( job->name() );
            qDebug() << "Jobs_2: " <<  m_jobs.size();
            m_lock.unlock();
            qDebug() << "Got Job: " << job->name();

            if( ! isCancelled ) {
                emit executionStarted( job->name(), job->category() );
                RespFunc func = job->execute();
                emit executionFinished( job->name(), job->category() );
                if( func ) {
                    if( job->shouldPostResponse() ) {
                        QCoreApplication::postEvent(
                                    this,
                                    new CallbackEvent( func ),
                                    100 );
                    }
                    else {
                        func();
                    }
                }
            }
            else {
                emit jobDescarded( job->name(), job->category() );
            }
            qDebug() << "Finished Job: " << job->name();
            delete job;
        }
        else {
            this->sleep( 1 );
        }
    }
}

bool JobManager::event( QEvent *event )
{
    if( event->type() == CallbackEvent::EVENT_TYPE ) {
        CallbackEvent *callbackEvt = static_cast< CallbackEvent *>( event );
        callbackEvt->invokeCallback();
    }
    return QThread::event( event );
}

} //end of namespace
