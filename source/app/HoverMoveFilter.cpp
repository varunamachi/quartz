#include "HoverMoveFilter.h"
#include "QuartzWindow.h"

namespace Vam { namespace Quartz {

HoverMoveFilter::HoverMoveFilter( QObject *parent )
    : QObject( parent )
{

}

bool HoverMoveFilter::eventFilter( QObject *obj, QEvent *event )
{
    if( event->type() == QEvent::HoverMove ) {
        QHoverEvent *mouseHoverEvent = static_cast<QHoverEvent *>( event );
        QuartzWindow *qzwindow = static_cast< QuartzWindow * >( obj );
        qzwindow->mouseMove( mouseHoverEvent->pos(),
                             mouseHoverEvent->oldPos() );
    }
    // standard event processing
    return QObject::eventFilter(obj, event);
}


} }
