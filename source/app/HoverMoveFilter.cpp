#include <QEvent>
#include <QHoverEvent>

#include "HoverMoveFilter.h"
#include "QuartzFramelessWindow.h"

namespace Quartz {

HoverMoveFilter::HoverMoveFilter(QObject* parent)
    : QObject(parent) {
}

bool HoverMoveFilter::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::HoverMove) {
        QHoverEvent* mouseHoverEvent = static_cast<QHoverEvent*>(event);
        QuartzFramelessWindow* qzwindow = static_cast<QuartzFramelessWindow*>(
            obj);
        qzwindow->mouseMove(mouseHoverEvent->pos(), mouseHoverEvent->oldPos());
    }
    // standard event processing
    return QObject::eventFilter(obj, event);
}

} // namespace Quartz
