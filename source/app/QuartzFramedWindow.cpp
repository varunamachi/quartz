
#include <QHBoxLayout>

#include <base/QzAppContext.h>
#include <base/notification/NotificationService.h>

#include "QzMainWidget.h"
#include "QuartzFramedWindow.h"

namespace Quartz {

QuartzFramedWindow::QuartzFramedWindow(QWidget* parent)
    : QMainWindow(parent) {
    this->setCentralWidget(new QzMainWidget(this));
}

QuartzFramedWindow::~QuartzFramedWindow() {
}

void QuartzFramedWindow::moveEvent(QMoveEvent* /*event*/) {
    auto notificationService = appContext()->notificationService();
    if (notificationService != nullptr) {
        notificationService->reposition();
    }
}

} // namespace Quartz
