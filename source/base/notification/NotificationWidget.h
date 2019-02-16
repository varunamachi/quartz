#pragma once

#include <memory>

#include <QWidget>
#include <QDateTime>

namespace Quartz {

enum class NotificationType : int
{
    Info,
    Warning,
    Error,
};

struct Msg
{
    Msg() {}

    Msg(int id,
        const QString &msg,
        NotificationType type,
        QTime time,
        QDateTime dateTime)
        : m_id(id)
        , m_msg(msg)
        , m_type(type)
        , m_time(time)
        , m_dateTime(dateTime)
    {

    }

    int m_id;

    QString m_msg;

    NotificationType m_type;

    QTime m_time;

    QDateTime m_dateTime;

};

class NotificationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NotificationWidget(Msg &&msg, QWidget *parent = nullptr);

    const Msg & msg() const;

    int id() const;

Q_SIGNALS:
    void closed();

private:
    Msg m_msg;
};


}
