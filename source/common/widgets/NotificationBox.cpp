
#include <QTimer>
#include <QLabel>
#include <QFont>
#include <QPainter>
#include <QPaintEvent>
#include <QCoreApplication>
#include <QPropertyAnimation>
#include <QDebug>
#include <QStaticText>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QCursor>

#include "NotificationBox.h"

namespace Quartz {

struct Colors {
    QColor bg;
    QColor fg;
};


inline uint qHash(const NotificationType &t, uint seed) {
    return ::qHash(static_cast<int>(t), seed);
}

const QHash<NotificationType, QString> COL = {
    { NotificationType::Info,    {
          "background-color: #AA03A556;  color: white" }
    },
    { NotificationType::Warning, {
          "background-color: #AAB3A60B;  color: white" }
    },
    { NotificationType::Error,   {
          "background-color: #AAB1543B;  color: white" }
    },
};

namespace
{
    const int DISPLAY_TIME = 1500;
}

struct NotificationBox::Data {
    Data(NotificationType type,
         const QString &text,
         int milliseconds,
         QWidget *parent)
        : m_type(type)
        , m_label(text)
        , m_opacity(1.0)
        , m_milliseconds(milliseconds)
        , m_parent(parent)
    {

    }

    NotificationType m_type;

    QStaticText m_label;

    qreal m_opacity;

    int m_milliseconds;

    QWidget *m_parent;
};

NotificationBox::NotificationBox(NotificationType type,
                                 const QString& text,
                                 QWidget* parent)
    : NotificationBox(type, text, QFont{}, DISPLAY_TIME, parent)
{}

NotificationBox::NotificationBox(
        NotificationType type,
        const QString& text,
        const QFont& font,
        int milliseconds,
        QWidget* parent)
    : QWidget(parent)
    , m_data(std::make_unique<Data>(type, text, milliseconds, parent))
{
    setFont(font);
    m_data->m_label.prepare(QTransform(), font);
    setWindowFlags(windowFlags()
                   | Qt::FramelessWindowHint
                   | Qt::WindowStaysOnTopHint
                   | Qt::Popup);

//    setAttribute(Qt::WA_NoSystemBackground);
//    setAttribute(Qt::WA_TranslucentBackground);
//    setAttribute(Qt::WA_PaintOnScreen);
//    setAttribute(Qt::WA_TransparentForMouseEvents);

    auto label = new QLabel(this);
    label->setText(text);
    auto lyt = new QVBoxLayout();
    lyt->addWidget(label);
    this->setLayout(lyt);
    auto point = m_data->m_parent->mapToGlobal(
                QPoint(m_data->m_parent->width() / 2,
                       m_data->m_parent->height() / 2));
    this->setGeometry(point.x() - 200, point.y() - 30, 200, 30);
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

void NotificationBox::resizeEvent(QResizeEvent *event)
{

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

//void NotificationBox::paintEvent(QPaintEvent* event)
//{
//    QPainter p{this};

//    p.setOpacity(m_data->m_opacity);
//    p.fillRect(event->rect(), COL[m_data->m_type].bg);
//    p.setPen(COL[m_data->m_type].fg);
//    p.drawRect(event->rect().adjusted(0, 0, -1, -1));
//    p.setFont(font());

//    auto halfSize = m_data->m_label.size().toSize() / 2;
//    auto pt = rect().center() - QPoint{halfSize.width(), halfSize.height()};
//    p.drawStaticText(pt, m_data->m_label);
//}


}
