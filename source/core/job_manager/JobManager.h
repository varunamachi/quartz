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

#include <functional>
#include <QThread>
#include <QQueue>
#include <QSet>
#include <QReadWriteLock>

#include "../utils/Macros.h"
#include "../QuartzCore.h"

namespace Quartz {

typedef std::function< void() > RespFunc;
typedef std::function< RespFunc() > JobFunc;


QZ_INTERFACE IJob
{
    virtual const QString& name() const = 0;

    virtual const QString& category() const = 0;

    virtual bool shouldPostResponse() const = 0;

    virtual RespFunc execute() = 0;

    virtual ~IJob();
};


class QUARTZ_CORE_API JobManager : public QThread
{
    Q_OBJECT

public:
    explicit JobManager(QObject *parent = nullptr);

    bool hasPendingJobs();

signals:
    void executionFinished(QString name, QString category);

    void executionStarted(QString name, QString category);

    void allJobsFinished();

    void jobDescarded(const QString name, const QString category);

public slots:
    void addJob(IJob *job);

    void addJob(QString name,
                 JobFunc job,
                 QString category = "general",
                 bool postResponseToEventQueue = true);

    bool cancelJob(QString name);

    bool cancelJobCategory(QString category);

    void cancelAll();

protected:
    void run();

    bool event(QEvent *event);

private:
    QReadWriteLock m_lock;

    QQueue<IJob *> m_jobs;

    QSet<QString> m_cancelledJobs;

    QSet<QString> m_cancelledCategories;

    bool m_stopProcessing;
};

} //end of namespace

