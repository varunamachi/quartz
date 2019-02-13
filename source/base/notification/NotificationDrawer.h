#pragma once

#include <memory>

#include <QWidget>

#include "../QuartzBase.h"

namespace Quartz {

class QUARTZ_BASE_API NotificationDrawer : public QWidget
{
    Q_OBJECT
public:
    NotificationDrawer(QWidget *parent);

    ~NotificationDrawer() override;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}
