
#include "NotificationDrawer.h"

namespace Quartz {

struct NotificationDrawer::Data
{
    explicit Data(NotificationDrawer * /*parent*/ )
    {

    }
};

NotificationDrawer::NotificationDrawer(QWidget *parent)
    : QWidget(parent)
{

}

NotificationDrawer::~NotificationDrawer()
{

}

}
