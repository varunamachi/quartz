
#include <QTimer>
#include <QLabel>
#include <QFont>
#include <QPainter>
#include <QPaintEvent>
#include <QCoreApplication>
#include <QPropertyAnimation>
#include <QDebug>
#include <QStaticText>

#include "NotificationBox.h"

namespace Quartz {

struct Colors {
    QColor bg;
    QColor fg;
};


inline uint qHash(const NotificationType &t, uint seed) {
    return ::qHash(static_cast<int>(t), seed);
}

const QHash<NotificationType, Colors> COL = {
    { NotificationType::Info,    { Qt::green,  Qt::white }},
    { NotificationType::Warning, { Qt::yellow, Qt::white }},
    { NotificationType::Error,   { Qt::red,    Qt::white }},
};

namespace
{
    const int DISPLAY_TIME = 1500;
}

struct NotificationBox::Data {
    Data(NotificationType type, const QString &text, int milliseconds)
        : m_type(type)
        , m_label(text)
        , m_opacity(1.0)
        , m_milliseconds(milliseconds)
    {

    }

    NotificationType m_type;

    QStaticText m_label;

    qreal m_opacity;

    int m_milliseconds;
};

NotificationBox::NotificationBox(NotificationType type,
                                 const QString& text,
                                 QWidget* parent)
    : NotificationBox(type, text, this->font(), DISPLAY_TIME, parent)
{}

NotificationBox::NotificationBox(
        NotificationType type,
        const QString& text,
        const QFont& font,
        int milliseconds,
        QWidget* parent)
    : QWidget(parent)
    , m_data(std::make_unique<Data>(type, text, milliseconds))
{
    setFont(font);
    m_data->m_label.prepare(QTransform(), font);
    setWindowFlags(windowFlags()
                   | Qt::FramelessWindowHint
                   | Qt::WindowStaysOnTopHint);
    if (parent) {
        auto x = static_cast<int>(m_data->m_label.size().width() / 2 + 20);
        auto y = static_cast<int>(m_data->m_label.size().height() / 2 + 20);
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
    QWidget::show();
    QCoreApplication::processEvents();
}

void NotificationBox::run()
{
    QWidget::show();
    update();
    QTimer::singleShot(m_data->m_milliseconds,
                       this,
                       &NotificationBox::fadeOut);
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
    m_data->m_opacity = opacity;
    update();
}

qreal NotificationBox::opacity() const
{
    return m_data->m_opacity;
}

void NotificationBox::show(
        NotificationType type,
        const QString& message,
        const QFont& font,
        int milliseconds,
        QWidget* parent)
{
    (new NotificationBox(type, message, font, milliseconds, parent))->run();
}

void NotificationBox::show(NotificationType type,
                           const QString& message,
                           QWidget* parent)
{
     (new NotificationBox(type, message, parent))->run();
}

void NotificationBox::show(NotificationType type,
                           const QString& message,
                           const QFont& font,
                           QWidget* parent)
{
    show(type, message, font, DISPLAY_TIME, parent);
}

void NotificationBox::paintEvent(QPaintEvent* event)
{
    QPainter p{this};

    p.setOpacity(m_data->m_opacity);
    p.fillRect(event->rect(), COL[m_data->m_type].bg);
    p.setPen(COL[m_data->m_type].fg);
    p.drawRect(event->rect().adjusted(0, 0, -1, -1));
    p.setFont(font());

    auto halfSize = m_data->m_label.size().toSize() / 2;
    auto pt = rect().center() - QPoint{halfSize.width(), halfSize.height()};
    p.drawStaticText(pt, m_data->m_label);
//    p.drawStaticText(rect().center() -= QPoint(
//                halfSize.width(), halfSize.height()), m_data->m_label);
}


}
