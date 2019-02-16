//#pragma once

//#include <memory>

//#include <QWidget>
//#include <QTime>
//#include <QVector>

//#include "../QuartzCommon.h"

//class QLabel;

//namespace Quartz {

//enum class NotificationType
//{
//    Info,
//    Warning,
//    Error,
//};

//struct Msg
//{
////    Msg() {}

//    Msg(const QString &msg, NotificationType type, QTime time)
//        : m_msg(msg)
//        , m_type(type)
//        , m_time(time)
//    {

//    }

//    QString m_msg;

//    NotificationType m_type;

//    QTime m_time;

//};


//class QUARTZ_COMMON_API NotificationBox : public QWidget
//{
//    Q_OBJECT
//    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

//public:


//    explicit NotificationBox(
//            const QVector<Msg>& texts,
//            QWidget* parent = nullptr);

//    explicit NotificationBox(
//            const QVector<Msg>& texts,
//            const QFont& font,
//            int milliseconds,
//            QWidget* parent = nullptr);

//    virtual ~NotificationBox() override;

//    void showImmediatly();

//    void run();

//    void fadeOut();

//    void setOpacity(qreal opacity);

//    qreal opacity() const;

//public:
//    static void show(NotificationType type,
//                     const QString& message,
//                     QWidget* parent);

//    static void show(const QVector<Msg>& messages, QWidget* parent);

//protected:
//    void resizeEvent(QResizeEvent *event) override;


//private:
//    struct Data;
//    std::unique_ptr<Data> m_data;
//};

//}
