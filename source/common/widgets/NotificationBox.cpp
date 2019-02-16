
//#include <QTimer>
//#include <QLabel>
//#include <QFont>
//#include <QPainter>
//#include <QPaintEvent>
//#include <QCoreApplication>
//#include <QPropertyAnimation>
//#include <QDebug>
//#include <QStaticText>
//#include <QVBoxLayout>
//#include <QResizeEvent>
//#include <QApplication>
//#include <QDesktopWidget>
//#include <QCursor>
//#include <QPushButton>

//#include "../iconstore/IconFontStore.h"
//#include "NotificationBox.h"

//namespace Quartz {


//const QString ICSS ="#ngbox {"
//                    "   border-color: rgba(24, 122, 220, 0.5);"
//                    "   border-left-color: rgba(24, 122, 220, 0.5);"
//                    "   border-style: solid;"
//                    "   border-width: 1px;"
//                    "   border-left-width: 6px;"
//                    "   padding: 10px;"
//                    "}";
//const QString WCSS ="#ngbox {"
//                    "   border-color: rgba(179, 143, 0, 0.5);"
//                    "   border-left-color: rgba(179, 143, 0, 0.5);"
//                    "   border-style: solid;"
//                    "   border-width: 1px;"
//                    "   border-left-width: 6px;"
//                    "   padding: 10px;"
//                    "}";
//const QString ECSS ="#ngbox {"
//                    "   border-color: rgba(204, 41, 0, 0.5);"
//                    "   border-left-color: rgba(204, 41, 0, 0.5);"
//                    "   border-style: solid;"
//                    "   border-width: 1px;"
//                    "   border-left-width: 6px;"
//                    "   padding: 10px;"
//                    "}";

//namespace
//{
//const QSize ICON_SIZE = {32, 32};
//const int DISPLAY_TIME = 2000;

//const QPixmap & icon(NotificationType type) {
//    if (type == NotificationType::Info) {
//        static auto INFO = getIcon(
//                    MatIcon::Done, {24, 122, 220}).pixmap(ICON_SIZE);
//        return INFO;
//    } else if(type == NotificationType::Warning) {
//        static auto WARN = getIcon(
//                    MatIcon::Warning, {179, 143, 0}).pixmap(ICON_SIZE);
//        return WARN;
//    }
//    static auto ERR  = getIcon(
//                MatIcon::Error, {204, 41, 0}).pixmap(ICON_SIZE);
//    return ERR;
//}

//}

//struct NotificationBox::Data {
//    Data(int milliseconds, QWidget *parent)
//        : m_opacity(1.0)
//        , m_milliseconds(milliseconds)
//        , m_parent(parent)
//    {

//    }

//    qreal m_opacity;

//    int m_milliseconds;

//    QWidget *m_parent;
//};

//NotificationBox::NotificationBox(const QVector<Msg>& texts, QWidget* parent)
//    : NotificationBox(texts, QFont{}, DISPLAY_TIME, parent)
//{}

//NotificationBox::NotificationBox(
//        const QVector<Msg>& texts,
//        const QFont& font,
//        int milliseconds,
//        QWidget* parent)
//    : QWidget(parent)
//    , m_data(std::make_unique<Data>(milliseconds, parent))
//{
//    setFont(font);
//    setWindowFlags(windowFlags()
//                   | Qt::FramelessWindowHint
//                   | Qt::WindowStaysOnTopHint
//                   | Qt::Popup
//                );
//    auto mainLayout = new QVBoxLayout();
//    mainLayout->setSpacing(8);
//    auto widget = new QWidget();
//    widget->setAttribute( Qt::WA_TranslucentBackground, true );
//    this->setAttribute( Qt::WA_TranslucentBackground, true );
//    widget->setLayout(mainLayout);

//    for (const auto &msg : texts) {
//        auto label = new QLabel(this);
//        label->setText(msg.m_msg);
//        label->setWordWrap(true);
//        auto icn = new QLabel(this);
//        icn->setPixmap(icon(msg.m_type));
//        auto closeBtn = new QPushButton(getIcon(FAIcon::Times), "", this);
//        connect(closeBtn, &QPushButton::released, [this]() {
//            this->hide();
//            this->deleteLater();
//        });
//        auto ml = new QHBoxLayout();
//        ml->addWidget(icn);
//        ml->addWidget(label);
//        ml->addWidget(closeBtn);

//        auto msgWidget = new QWidget(this);
//        msgWidget->setObjectName("ngbox");
//        msgWidget->setLayout(ml);

//        switch (msg.m_type) {
//        case NotificationType::Info:    msgWidget->setStyleSheet(ICSS); break;
//        case NotificationType::Warning: msgWidget->setStyleSheet(WCSS); break;
//        case NotificationType::Error:   msgWidget->setStyleSheet(ECSS); break;
//        }

//        mainLayout->addWidget(msgWidget);
//    }

//    auto lyt = new QVBoxLayout();
//    lyt->addWidget(widget);
//    this->setLayout(lyt);

//    this->setMinimumSize({200, 50});
//    setContentsMargins({});
//    widget->setContentsMargins({});
//    lyt->setContentsMargins({});
//}

//NotificationBox::~NotificationBox()
//{
//}

//void NotificationBox::showImmediatly()
//{
//    QWidget::show();
//    QCoreApplication::processEvents();
//}

//void NotificationBox::run()
//{
//    QWidget::show();
//    update();
//    QTimer::singleShot(m_data->m_milliseconds,
//                       this,
//                       &NotificationBox::fadeOut);
//}

//void NotificationBox::fadeOut()
//{
//    auto animation = new QPropertyAnimation(this, "opacity", this);
//    connect(animation,
//            &QPropertyAnimation::finished,
//            this,
//            &NotificationBox::deleteLater);
//    animation->setDuration(1000);
//    animation->setStartValue(1.0);
//    animation->setEndValue(0.0);
//    animation->start(QAbstractAnimation::DeleteWhenStopped);
//}

//void NotificationBox::setOpacity(qreal /*opacity*/)
//{
////    this->setWindowOpacity(opacity);
////    this->setStyleSheet(QStringLiteral("opacity: %1").arg(opacity));
////    m_data->m_opacity = opacity;
////    update();
//}

//qreal NotificationBox::opacity() const
//{
//    return m_data->m_opacity;
//}

//void NotificationBox::resizeEvent(QResizeEvent * /*event*/)
//{
//    auto point = m_data->m_parent->mapToGlobal({0, 0});
//    this->move(static_cast<int>(point.x() - this->width() + 10),
//               static_cast<int>(point.y() - this->height()));
//}

//void NotificationBox::show(NotificationType type,
//                           const QString& message,
//                           QWidget* parent)
//{
//    auto msgs = QVector<Msg>{{message, type, QTime::currentTime()}};
//    (new NotificationBox(msgs, parent))->run();
//}

//void NotificationBox::show(const QVector<Msg> &messages,
//                           QWidget *parent)
//{
//    (new NotificationBox(messages, parent))->run();
//}

//}
