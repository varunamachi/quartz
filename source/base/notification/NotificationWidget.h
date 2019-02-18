#pragma once

#include <memory>

#include <QWidget>
#include <QDateTime>

#include "../QuartzBase.h"

namespace Quartz {

class Msg;

//enum class NotificationType : int
//{
//    Info,
//    Warning,
//    Error,
//};

//struct Msg
//{
//    Msg() {}

//    Msg(int id,
//        const QString &msg,
//        NotificationType type,
//        QTime time,
//        QDateTime dateTime)
//        : m_id(id)
//        , m_msg(msg)
//        , m_type(type)
//        , m_time(time)
//        , m_dateTime(dateTime)
//    {

//    }

//    int m_id;

//    QString m_msg;

//    NotificationType m_type;

//    QTime m_time;

//    QDateTime m_dateTime;

//};

class QUARTZ_BASE_API NotificationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NotificationWidget(
            std::shared_ptr<Msg> msg,
            QWidget *parent = nullptr);

    ~NotificationWidget() override;

    const Msg * msg() const;

Q_SIGNALS:
    void closed();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    struct Data;
    std::unique_ptr<Data> m_data;

};


}
