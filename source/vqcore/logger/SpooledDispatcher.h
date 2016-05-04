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

#include <memory>

#include <QThread>
#include <QQueue>
#include <QHash>
#include <QReadWriteLock>

#include "VQLogger.h"
#include "../VQ.h"

namespace Vam { namespace Logger {



class VQ_CORE_EXPORT SpooledDispatcher : public QThread
                                       , public ILogDispatcher
{
    Q_OBJECT
public:
    SpooledDispatcher( QObject *parent );

    bool addTarget( AbstractLogTarget *target );

    AbstractLogTarget * target( QString targetId );

    bool setTargetEnabledState( const QString &trgId, bool value );

    bool removeTarget( const QString &targetId );

    bool installFilter( ILogFilter *filter,
                        const QString &trgtId );

    bool uninstallFilter( const QString &filterId,
                          const QString &trgtId );

    void write( LogMessage *message );

    void flush();

    void stopDispatch();

    ~SpooledDispatcher();

protected:
    void run();

private:
    struct TargetInfo
    {
        TargetInfo( AbstractLogTarget *target, bool enable )
            : m_target( target )
            , m_enabled( enable ) {}

        ~TargetInfo()
        {
            delete m_target;
        }

        AbstractLogTarget *m_target;

        bool m_enabled;

        QList< ILogFilter *> m_targetFilters;
    };

    struct FilterInfo
    {
        FilterInfo( ILogFilter *filter )
            : m_filter( filter )
            , m_refs( 0 )
            , m_enabled( true ) {}

        ~FilterInfo()
        {
            delete m_filter;
        }

        ILogFilter *m_filter;

        int m_refs;

        bool m_enabled;
    };

    void writeToTargets( LogMessage *msg );

    bool m_stop;

    QQueue< LogMessage *> m_logQueue;

    QHash< QString, FilterInfo *> m_allFilters;

    QHash< QString, TargetInfo *> m_targets;

    QReadWriteLock m_lock;

    QReadWriteLock m_logIoLock;

    bool m_shouldStop;

};

} } // end of namespaces

