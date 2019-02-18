
#include <QTime>
#include <QQueue>
#include <QMutex>
#include <QReadWriteLock>
#include <QTimer>
#include <QVector>
#include <QVBoxLayout>
#include <QCoreApplication>
#include <QGraphicsOpacityEffect>
#include <QDebug>

#include <core/utils/ScopedOperation.h>

#include "../QzAppContext.h"
#include "view_manager/ViewManager.h"
#include "Msg.h"
#include "MsgView.h"
#include "NotificationService.h"
#include "NotificationWidget.h"

namespace Quartz {

const auto DURATION_SECS = 5;

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
                   | Qt::Dialog
                );
    this->setAttribute(Qt::WA_TranslucentBackground);
    m_data->m_layout->setSizeConstraint(QLayout::SetFixedSize);
    this->setLayout(m_data->m_layout);

    connect(m_data->m_timer,
            &QTimer::timeout,
            [=]() {
        this->refresh();
    });
    m_data->m_timer->start(1000);
    m_data->m_layout->setContentsMargins({});
}

NotificationService::~NotificationService()
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
        if (nw->msg()->time().secsTo(QTime::currentTime()) > DURATION_SECS) {
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
    m_data->m_id = (m_data->m_id + 1) % 10000;
    auto obj = std::make_shared<Msg>(
            m_data->m_id,
            msg,
            type,
            QTime::currentTime(),
            QDateTime::currentDateTime());
    //add to model too...
    auto view = appContext()->viewManager()->view<MsgView>(MsgView::VIEW_ID);
    if (view != nullptr) {
        view->addMessage(obj);
    }
    auto nw = new NotificationWidget(obj, this);
    connect(nw, &NotificationWidget::closed, [=]() {
        m_data->m_layout->removeWidget(nw);
        nw->hide();
        nw->deleteLater();
    });
    m_data->m_layout->addWidget(nw);
    if (! isVisible()) {
        QWidget::show();
    }
    update();
}

void NotificationService::clear()
{
    auto time = QTime::currentTime();
    while(m_data->m_layout->count() != 0) {
        auto nw = qobject_cast<NotificationWidget *>(
                    m_data->m_layout->itemAt(0)->widget());
        if (nw == nullptr) {
            continue;
        }
        if (nw->msg()->time().secsTo(time) > 0) {
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

void NotificationService::reposition()
{
    auto point = m_data->m_parent->mapToGlobal({0, 0});
    this->move(static_cast<int>(point.x() - this->width() + 10),
               static_cast<int>(point.y() - this->height()));

}

void NotificationService::resizeEvent(QResizeEvent * /*event*/)
{
    reposition();
}

void NotificationService::info(const QString &msg)
{
    QTimer::singleShot(0, [=]() {
        add(NotificationType::Info, msg);
    });
}

void NotificationService::warn(const QString &msg)
{
    QTimer::singleShot(0, [=]() {
        add(NotificationType::Warning, msg);
    });
}

void NotificationService::error(const QString &msg)
{
    QTimer::singleShot(0, [=]() {
        add(NotificationType::Error, msg);
    });
}

}
