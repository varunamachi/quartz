
#include <QTimer>
#include <QLabel>
#include <QFont>
#include <QPainter>
#include <QPaintEvent>
#include <QCoreApplication>
#include <QPropertyAnimation>
#include <QDebug>

#include "NotificationBox.h"

namespace Quartz {


namespace
{
    const QColor FILL_COLOR(66, 68, 70);
    const QColor TEXT_COLOR(188, 190, 191);

    const QFont FONT("Segoe UI", 16);
    const int DISPLAY_TIME = 1500;
}

NotificationBox::NotificationBox(const QString& text,
                                 QWidget* parent)
    : NotificationBox(text, FONT, DISPLAY_TIME, parent)
{}

NotificationBox::NotificationBox(
        const QString& text,
        const QFont& font,
        int milliseconds,
        QWidget* parent)
    : QWidget(parent)
    , m_label(text)
    , m_opacity(1.0)
    , m_milliseconds(milliseconds)
{
    setFont(font);
    m_label.prepare(QTransform(), font);
    setWindowFlags(windowFlags()
                   | Qt::FramelessWindowHint
                   | Qt::WindowStaysOnTopHint);
    if (parent) {
        auto x = static_cast<int>(m_label.size().width() / 2 + 20);
        auto y = static_cast<int>(m_label.size().height() / 2 + 20);
        QPoint offset{x, y};
        setGeometry({parent->rect().center() - offset,
                     parent->rect().center() + offset});
    } else {
        resize(270, 80);
    }
}

NotificationBox::~NotificationBox()
{

}

void NotificationBox::showImmediatly()
{
    show();
    QCoreApplication::processEvents();
}

void NotificationBox::run()
{
    show();
    update();
    QTimer::singleShot(m_milliseconds, this, &NotificationBox::fadeOut);
}

void NotificationBox::fadeOut()
{
    auto animation = new QPropertyAnimation(this, "opacity", this);
    connect(animation,
            &QPropertyAnimation::finished,
            this,
            &NotificationBox::deleteLater);
    animation->setDuration(500);
    animation->setStartValue(1.0);
    animation->setEndValue(0.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void NotificationBox::setOpacity(qreal opacity)
{
    m_opacity = opacity;
    update();
}

qreal NotificationBox::opacity() const
{
    return m_opacity;
}

void NotificationBox::showMessage(
        const QString& message,
        const QFont& font,
        int milliseconds,
        QWidget* parent)
{
    (new NotificationBox(message, font, milliseconds, parent))->run();
}

void NotificationBox::showMessage(const QString& message, QWidget* parent)
{
    showMessage(message, FONT, parent);
}

void NotificationBox::showMessage(const QString& message,
                                  const QFont& font,
                                  QWidget* parent)
{
    showMessage(message, font, DISPLAY_TIME, parent);
}

void NotificationBox::paintEvent(QPaintEvent* event)
{
    QPainter p{this};

    p.setOpacity(m_opacity);
    p.fillRect(event->rect(), FILL_COLOR);
    p.setPen(TEXT_COLOR);
    p.drawRect(event->rect().adjusted(0, 0, -1, -1));
    p.setFont(font());

    auto halfSize = m_label.size().toSize() / 2;
    auto pt = rect().center() - QPoint{halfSize.width(), halfSize.height()};
    p.drawStaticText(pt, m_label);
//    p.drawStaticText(rect().center() -= QPoint(
//                halfSize.width(), halfSize.height()), m_label);
}


}
