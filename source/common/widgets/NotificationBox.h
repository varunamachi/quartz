#pragma once

#include <memory>

#include <QWidget>

#include "../QuartzCommon.h"

class QLabel;

namespace Quartz {


enum class NotificationType
{
    Info,
    Warning,
    Error,
};

class QUARTZ_COMMON_API NotificationBox : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:


    explicit NotificationBox(
            NotificationType ntype,
            const QString& text,
            QWidget* parent = nullptr);

    explicit NotificationBox(
            NotificationType ntype,
            const QString& text,
            const QFont& font,
            int milliseconds,
            QWidget* parent = nullptr);

    virtual ~NotificationBox() override;

    void showImmediatly();

    void run();

    void fadeOut();

    void setOpacity(qreal opacity);

    qreal opacity() const;

public:
    static void show(NotificationType type,
                     const QString& message,
                     QWidget* parent);

    static void show(NotificationType type,
                     const QString& message,
                     const QFont& font,
                     QWidget* parent);

    static void show(NotificationType type,
                     const QString& message,
                     const QFont& font,
                     int milliseconds,
                     QWidget* parent);

protected:


private:
    struct Data;
    std::unique_ptr<Data> m_data;



    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};

}
