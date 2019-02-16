
#include <QTime>
#include <QQueue>
#include <QMutex>
#include <QReadWriteLock>
#include <QTimer>
#include <QVector>
#include <QVBoxLayout>
#include <QCoreApplication>

#include <core/utils/ScopedOperation.h>

#include "NotificationService.h"
#include "NotificationWidget.h"

namespace Quartz {

const auto DURATION_SECS = 4;

struct NotificationService::Data
{
    explicit Data(QWidget *widget)
        : m_parent(widget)
        , m_layout(new QVBoxLayout())
        , m_timer(new QTimer(widget))
        , m_id(0)
    {
        m_layout->setDirection(QBoxLayout::Up);
    }

    QWidget *m_parent;

    QVBoxLayout *m_layout;

    QTimer *m_timer;

    int m_id;

    QReadWriteLock m_lock;
};


NotificationService::NotificationService(QWidget *parent)
    : QWidget(parent)
    , m_data(std::make_unique<Data>(parent))
{
    setWindowFlags(windowFlags()
                   | Qt::FramelessWindowHint
                   | Qt::WindowStaysOnTopHint
                   | Qt::Popup
                );
    this->setAttribute(Qt::WA_TranslucentBackground, true);


    setContentsMargins({});
    m_data->m_layout->setSizeConstraint(QLayout::SetFixedSize);
    m_data->m_layout->setContentsMargins({});

    auto widget = new QWidget();
//    widget->setAttribute(Qt::WA_TranslucentBackground, true);
    widget->setLayout(m_data->m_layout);
    auto lyt = new QVBoxLayout();
    lyt->addWidget(widget);
    this->setLayout(lyt);
    widget->setContentsMargins({});
    lyt->setContentsMargins({});
    lyt->setSizeConstraint(QLayout::SetFixedSize);
    connect(m_data->m_timer,
            &QTimer::timeout,
            [=]() {
        this->refresh();
    });
    m_data->m_timer->start(1000);
}

NotificationService::~NotificationService()
{
}

void NotificationService::run()
{

}

void NotificationService::refresh()
{
    while(m_data->m_layout->count() != 0) {
        auto nw = qobject_cast<NotificationWidget *>(
                    m_data->m_layout->itemAt(0)->widget());
        if (nw == nullptr) {
            continue;
        }
        if (nw->msg().m_time.secsTo(QTime::currentTime()) > DURATION_SECS) {
            m_data->m_layout->removeWidget(nw);
            nw->hide();
            nw->deleteLater();
        } else {
            break;
        }
        QCoreApplication::processEvents();
    }
    if (m_data->m_layout->count() == 0) {
        this->hide();
    }
}

void NotificationService::add(NotificationType type, const QString &msg)
{
//    SCOPE_LIMIT(m_data->m_lock.lockForWrite(), m_data->m_lock.unlock());
    m_data->m_id = (m_data->m_id + 1) % 10000;
    auto obj = Msg{
            m_data->m_id,
            msg,
            type,
            QTime::currentTime(),
            QDateTime::currentDateTime()};
    auto nw = new NotificationWidget(std::move(obj), this);
    m_data->m_layout->addWidget(nw);
    QWidget::show();
    update();
}

void NotificationService::resizeEvent(QResizeEvent * /*event*/)
{
    auto point = m_data->m_parent->mapToGlobal({0, 0});
    this->move(static_cast<int>(point.x() - this->width() + 10),
               static_cast<int>(point.y() - this->height()));
}

void NotificationService::info(const QString &msg)
{
    add(NotificationType::Info, msg);
//    QTimer::singleShot(0, [=]() {
//    });
}

void NotificationService::warn(const QString &msg)
{
    add(NotificationType::Warning, msg);
//    QTimer::singleShot(0, [=]() {
//    });
}

void NotificationService::error(const QString &msg)
{
    add(NotificationType::Error, msg);
//    QTimer::singleShot(0, [=]() {
//    });
}

}
