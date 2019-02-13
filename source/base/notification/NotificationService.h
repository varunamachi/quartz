#pragma once

#include <memory>

#include "../QuartzBase.h"

class QWidget;
class QString;

namespace Quartz {

class QUARTZ_BASE_API NotificationService
{
public:
    NotificationService(QWidget *widget);

    ~NotificationService();

    void info(const QString &msg);

    void warn(const QString &msg);

    void error(const QString &msg);

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}
