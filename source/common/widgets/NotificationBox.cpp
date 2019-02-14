
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

#include "../iconstore/IconFontStore.h"
#include "NotificationBox.h"

namespace Quartz {


const QString ICSS ="#ngbox {"
                    "   border-color: rgba(24, 122, 220, 0.5);"
                    "   border-left-color: rgba(24, 122, 220, 0.5);"
                    "   border-style: solid;"
                    "   border-width: 1px;"
                    "   border-left-width: 6px;"
                    "   padding: 10px;"
                    "}";
const QString WCSS ="#ngbox {"
                    "   border-color: rgba(220, 199, 14, 0.5);"
                    "   border-left-color: rgba(220, 199, 14, 0.5);"
                    "   border-style: solid;"
                    "   border-width: 1px;"
                    "   border-left-width: 6px;"
                    "   padding: 10px;"
                    "}";
const QString ECSS ="#ngbox {"
                    "   border-color: rgba(220, 55, 14, 0.5);"
                    "   border-left-color: rgba(220, 55, 14, 0.5);"
                    "   border-style: solid;"
                    "   border-width: 1px;"
                    "   border-left-width: 6px;"
                    "   padding: 10px;"
                    "}";

namespace
{
const QSize ICON_SIZE = {32, 32};
const int DISPLAY_TIME = 1500;

const QPixmap & icon(NotificationType type) {
    if (type == NotificationType::Info) {
        static auto INFO =
                getIcon(MatIcon::Info, {24, 122, 220}).pixmap(ICON_SIZE);
        return INFO;
    } else if(type == NotificationType::Warning) {
        static auto WARN =
                getIcon(MatIcon::Warning, {220, 199, 14}).pixmap(ICON_SIZE);
        return WARN;
    }
    static auto ERR  = getIcon(MatIcon::Error, {220, 55, 14}).pixmap(ICON_SIZE);
    return ERR;
}

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
    setAttribute(Qt::WA_TranslucentBackground, true);

    auto label = new QLabel(this);
    label->setText(text);
    label->setWordWrap(true);
    auto icn = new QLabel(this);
    icn->setPixmap(icon(type));

    auto mainLayout = new QHBoxLayout();
    mainLayout->addWidget(icn);
    mainLayout->addWidget(label);

    auto widget = new QWidget();
    widget->setObjectName("ngbox");
    widget->setLayout(mainLayout);

    auto lyt = new QVBoxLayout();
//    lyt->addLayout(mainLayout);
    lyt->addWidget(widget);
    this->setLayout(lyt);

    switch (type) {
    case NotificationType::Info:    this->setStyleSheet(ICSS); break;
    case NotificationType::Warning: this->setStyleSheet(WCSS); break;
    case NotificationType::Error:   this->setStyleSheet(ECSS); break;
    }
    this->setMinimumSize({200, 50});
    setContentsMargins({});
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
    auto point = m_data->m_parent->mapToGlobal({0, 0});
//    this->move(point.x(), point.y());
    this->move(static_cast<int>(point.x() - this->width() + 20),
               static_cast<int>(point.y() - this->height()) + 10);
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
