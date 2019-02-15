
#include <QTime>
#include <QQueue>
#include <QMutex>
#include <QReadWriteLock>
#include <QTimer>

#include <core/utils/ScopedOperation.h>
#include <common/widgets/NotificationBox.h>

#include "NotificationService.h"

namespace Quartz {

struct Msg
{
    Msg(const QString &msg, NotificationType type, QTime time)
        : m_msg(msg)
        , m_type(type)
        , m_time(time)
    {

    }

    QString m_msg;

    NotificationType m_type;

    QTime m_time;

};

struct NotificationService::Data
{
    explicit Data(QWidget *widget)
        : m_widget(widget)
    {

    }

    inline void cleanExpired() {
        while(!m_msgs.isEmpty()) {
            if (m_msgs.head().m_time.secsTo(QTime::currentTime()) > 0) {
                m_msgs.dequeue();
            }
        }
    }

    inline void add(NotificationType type, const QString &msg)
    {
        SCOPE_LIMIT(m_lock.lockForWrite(), m_lock.unlock());
        cleanExpired();
        m_msgs.enqueue({msg, type, QTime::currentTime()});
    }

    inline QStringList getActive()
    {
        QStringList list;
        SCOPE_LIMIT(m_lock.lockForRead(), m_lock.unlock());
        for (const Msg &msg : m_msgs) {
            list << msg.m_msg;
        }
        return list;
    }


    QWidget *m_widget;

    QQueue<Msg> m_msgs;

    QReadWriteLock m_lock;
};


NotificationService::NotificationService(QWidget *widget)
    : m_data(std::make_unique<Data>(widget))
{

}

NotificationService::~NotificationService()
{
}

void NotificationService::info(const QString &msg)
{
//    m_data->add(msg);
    NotificationBox::show(NotificationType::Info, msg, m_data->m_widget);

}

void NotificationService::warn(const QString &msg)
{
    NotificationBox::show(NotificationType::Warning, msg, m_data->m_widget);
}

void NotificationService::error(const QString &msg)
{
    NotificationBox::show(NotificationType::Error, msg, m_data->m_widget);
}

}
