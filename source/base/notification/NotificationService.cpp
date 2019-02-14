
#include <common/widgets/NotificationBox.h>

#include "NotificationService.h"

namespace Quartz {

struct NotificationService::Data
{
    explicit Data(QWidget *widget)
        : m_widget(widget)
    {

    }

    QWidget *m_widget;
};


NotificationService::NotificationService(QWidget *widget)
    : m_data(std::make_unique<Data>(widget))
{

}

NotificationService::~NotificationService()
{
}

void NotificationService::info(const QString &msg)
{
    NotificationBox::show(NotificationType::Info, msg, m_data->m_widget);

}

void NotificationService::warn(const QString &msg)
{
    NotificationBox::show(NotificationType::Warning, msg, m_data->m_widget);
}

void NotificationService::error(const QString &msg)
{
    NotificationBox::show(NotificationType::Error, msg, m_data->m_widget);
}

}
