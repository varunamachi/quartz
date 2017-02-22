#include <memory>

#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSizeGrip>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QApplication>
#include <QStyle>
#include <QSplitter>

#include <base/title_bar/TitleBar.h>

#include "adapted/CustomShadowEffect.h"
#include "HoverMoveFilter.h"
#include "QzMainWidget.h"
#include "QuartzFramelessWindow.h"

#define WINDOW_MARGIN 5


namespace Quartz {

struct QuartzFramelessWindow::Data
{
    Data( QMainWindow *parent )
        : m_chilliWidget{ new QzMainWidget{ parent }}
        , m_moving{ false }
        , m_maximised{ false }
    {

    }

    QzMainWidget *m_chilliWidget;

    bool m_moving;

    bool m_maximised;

    QPoint m_lastMousePosition;

    QByteArray m_geometry;

    QHBoxLayout *m_layout;

    QWidget *m_containerWidget;

    bool m_cursorAtLeft;

    bool m_cursorAtRight;

    bool m_cursorAtBottom;

    bool m_resizing;

};

QuartzFramelessWindow::QuartzFramelessWindow( QWidget *parent )
    : QMainWindow( parent )
    , m_data{ new Data{ this }}
{
    m_data->m_containerWidget = new QWidget( this );

    setMouseTracking( true );
    setAttribute( Qt::WA_Hover );
    installEventFilter( new HoverMoveFilter( this ));

    m_data->m_layout = new QHBoxLayout( /*m_data->m_containerWidget*/ );
    m_data->m_layout->addWidget( m_data->m_chilliWidget );
    m_data->m_layout->setSpacing( 0 );
    m_data->m_containerWidget->setLayout( m_data->m_layout );

    this->setWindowFlags( Qt::FramelessWindowHint
                          | Qt::WindowMinimizeButtonHint );
#if 0
    m_data->m_containerWidget->setAttribute( Qt::WA_TranslucentBackground,
                                             true );
    this->setAttribute( Qt::WA_TranslucentBackground, true );
    CustomShadowEffect *effect = new CustomShadowEffect( this );
    effect->setBlurRadius( 10.0 );
    effect->setDistance( 3.0 );
    effect->setColor( QColor( 0xA0, 0x52, 0x2D, 0x80 ));
    m_data->m_chilliWidget->setGraphicsEffect( effect );
    m_data->m_containerWidget->setContentsMargins( 5, 5, 5, 5 );
    m_data->m_chilliWidget->setContentsMargins( 5, 5, 0, 0 );
    m_data->m_layout->setContentsMargins( 5, 5, 0, 0 );
#else
    m_data->m_containerWidget->setContentsMargins( 2, 2, 2, 2 );
    m_data->m_chilliWidget->setContentsMargins( 2, 2, 2, 2 );
    m_data->m_layout->setContentsMargins( 0, 0, 0, 0 );
    this->setStyleSheet( "QMainWindow{ border: 1px solid #FFA858; }");

//    CustomShadowEffect *effect = new CustomShadowEffect( this );
//    effect->setBlurRadius( 10.0 );
//    effect->setDistance( 3.0 );
//    effect->setColor( QColor( 0xA0, 0x52, 0x2D, 0x80 ));
//    this->setGraphicsEffect(effect);

#endif

    this->setContentsMargins( QMargins() );
    this->setCentralWidget( m_data->m_containerWidget );

    connect( m_data->m_chilliWidget->titleBar(),
             SIGNAL( sigCloseRequested() ),
             this,
             SLOT( close() ));
    connect( m_data->m_chilliWidget->titleBar(),
             SIGNAL( sigMaxRestoreRequested() ),
             this,
             SLOT( onMaximizeRestore() ));
    connect( m_data->m_chilliWidget->titleBar() ,
             SIGNAL( sigMinimizeRequested() ),
             this,
             SLOT( onMinimize() ));
}

QuartzFramelessWindow::~QuartzFramelessWindow()
{

}


void QuartzFramelessWindow::onMinimize()
{
    minimize();
}


void QuartzFramelessWindow::onMaximizeRestore()
{
    if( m_data->m_maximised ) {
        m_data->m_maximised = false;
        restore();
    }
    else {
        m_data->m_geometry = saveGeometry();
        m_data->m_maximised = true;
        maximize();
    }
}


void QuartzFramelessWindow::mousePressEvent( QMouseEvent* event )
{
    if( event->button() == Qt::LeftButton ) {
        m_data->m_moving = true;
        if( m_data->m_cursorAtLeft ) {
            m_data->m_lastMousePosition.setX( event->pos().x() );
        }
        if( m_data->m_cursorAtRight ) {
            m_data->m_lastMousePosition.setX( width() - event->pos().x() );
        }
        if( m_data->m_cursorAtBottom ) {
            m_data->m_lastMousePosition.setY( height() - event->pos().y() );
        }
        else {
            m_data->m_lastMousePosition = event->globalPos();
        }
        QMainWindow::mousePressEvent( event );
    }
}


void QuartzFramelessWindow::mouseMoveEvent( QMouseEvent* event )
{
    if( event->buttons().testFlag( Qt::LeftButton )
            && m_data->m_moving
            && ! m_data->m_resizing ) {
        QPoint newPos = this->pos()
                + ( event->globalPos() - m_data->m_lastMousePosition );
        if( newPos.y() <= 0 ) {
            m_data->m_maximised = true;
            emit maximize();
        }
        else if( m_data->m_maximised && newPos.y() >= 10 ) {
            m_data->m_maximised = false;
            restore();
            move( event->globalX() - this->width() / 2, event->globalY() );
        }
        else {
            move( newPos );
        }
        m_data->m_lastMousePosition = event->globalPos();
    }
    QWidget::mouseMoveEvent( event );
}


void QuartzFramelessWindow::mouseReleaseEvent( QMouseEvent* event )
{
    if( event->button() == Qt::LeftButton ) {
        m_data->m_moving = false;
        m_data->m_resizing = false;
    }
    QWidget::mouseReleaseEvent( event );
}


void QuartzFramelessWindow::showEvent( QShowEvent *evt )
{
    if( m_data->m_geometry.isEmpty() ) {
        m_data->m_geometry = this->saveGeometry();
    }
    QWidget::showEvent( evt );
}


void QuartzFramelessWindow::resizeEvent( QResizeEvent *evt )
{
    QWidget::resizeEvent( evt );
}



void QuartzFramelessWindow::maximize()
{
    QDesktopWidget *desktop = QApplication::desktop();
    // Because reserved space can be on all sides of the scren
    // you have to both move and resize the window
    m_data->m_layout->setSpacing( 0 );
    m_data->m_layout->setContentsMargins( QMargins() );
    m_data->m_containerWidget->setContentsMargins( QMargins() );
    m_data->m_chilliWidget->setRoundedRect( false );

    QRect rect = desktop->availableGeometry(
                desktop->screenNumber(QCursor::pos()));
    this->setGeometry( rect );
}


void QuartzFramelessWindow::restore()
{
    if( ! m_data->m_geometry.isEmpty() ) {
        m_data->m_layout->setSpacing( 0 );
        m_data->m_layout->setContentsMargins( 5, 5, 0, 0 );
        m_data->m_containerWidget->setContentsMargins( 5, 5, 5, 5 );
        m_data->m_chilliWidget->setRoundedRect( true );
        this->restoreGeometry( m_data->m_geometry );
    }
}


void QuartzFramelessWindow::minimize()
{
    if( ! this->isMinimized() ) {
        this->showMinimized();
    }
}


void QuartzFramelessWindow::mouseMove( QPoint newPos, QPoint oldPos )
{
    if( m_data->m_moving ) {
        int dx = newPos.x() - oldPos.x();
        int dy = newPos.y() - oldPos.y();
        QRect g = geometry();
        QSize minSize = minimumSize();

        // We don't resize if the windows has the minimum size
        if( m_data->m_cursorAtLeft ) {
            // Fix a bug when you try to resize to less than minimum size and
            // then the mouse goes right again.
            if ( dx < 0 && oldPos.x() > m_data->m_lastMousePosition.x() ) {
                dx += oldPos.x() - m_data->m_lastMousePosition.x();
                if( dx > 0 ) {
                    dx = 0;
                }
            }
            else if( dx > 0 && g.width() - dx < minSize.width() ) {
                dx = g.width() - minSize.width();
            }
            g.setLeft( g.left() + dx );
        }
        if( m_data->m_cursorAtRight ) {
            // Fix a bug when you try to resize to less than minimum size and
            // then the mouse goes right again.
            if( dx > 0 && ( width() - newPos.x()
                            > m_data->m_lastMousePosition.x() )) {
                dx -= width() - newPos.x() - m_data->m_lastMousePosition.x();
                if( dx < 0 ) {
                    dx = 0;
                }
            }
            g.setRight( g.right() + dx );
        }
        if( m_data->m_cursorAtBottom ) {
            // Fix a bug when you try to resize to less than minimum size and
            // then the mouse goes down again.
            if( dy > 0 && ( height() - newPos.y()
                            > m_data->m_lastMousePosition.y() )) {
                dy -= height() - newPos.y() - m_data->m_lastMousePosition.y();
                if (dy < 0) {
                    dy = 0;
                }
            }
            g.setBottom( g.bottom() + dy );
        }
        setGeometry( g );

    } else {
        QRect r = rect();
        m_data->m_cursorAtLeft =
                ( qAbs( newPos.x()- r.left() ) <= WINDOW_MARGIN )
                && newPos.y() > m_data->m_chilliWidget->titleBar()->height();
        m_data->m_cursorAtRight =
                ( qAbs(newPos.x() - r.right()) <= WINDOW_MARGIN )
                && newPos.y() > m_data->m_chilliWidget->titleBar()->height();
        m_data->m_cursorAtBottom =
                ( qAbs( newPos.y() - r.bottom() ) <= WINDOW_MARGIN );
        bool horizontal = m_data->m_cursorAtLeft || m_data->m_cursorAtRight;

        m_data->m_resizing = true;
        if( horizontal && m_data->m_cursorAtBottom ) {
            if( m_data->m_cursorAtLeft ) {
                setCursor( Qt::SizeBDiagCursor );
            }
            else {
                setCursor( Qt::SizeFDiagCursor );
            }
        }
        else if( horizontal ) {
            setCursor( Qt::SizeHorCursor );
        }
        else if( m_data->m_cursorAtBottom ) {
            setCursor( Qt::SizeVerCursor );
        }
        else {
            setCursor( Qt::ArrowCursor );
            m_data->m_resizing = false;
        }
    }
}

}
