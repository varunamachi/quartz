#pragma once

#include "../QzAppContext.h"
#include "NotificationService.h"

namespace Quartz {

inline void showInfo(const QString &msg)
{
    appContext()->notificationService()->info(msg);
}

inline void showWarning(const QString &msg)
{
    appContext()->notificationService()->warn(msg);
}

inline void showError(const QString &msg)
{
    appContext()->notificationService()->error(msg);
}

}
