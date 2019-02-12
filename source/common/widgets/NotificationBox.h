#pragma once

#include <QWidget>
#include <QStaticText>

#include "../QuartzCommon.h"

namespace Quartz {

class QLabel;

class QUARTZ_COMMON_API NotificationBox : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
    explicit NotificationBox(
            const QString& text,
            QWidget* parent = nullptr);

    explicit NotificationBox(
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
    static void showMessage(const QString& message,
                            QWidget* parent);

    static void showMessage(const QString& message,
                            const QFont& font,
                            QWidget* parent);

    static void showMessage(const QString& message,
                            const QFont& font,
                            int milliseconds,
                            QWidget* parent);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QStaticText m_label;
    qreal m_opacity;
    int m_milliseconds;
};

}
