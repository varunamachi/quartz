
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QApplication>
#include <QPainter>
#include <QStyle>

#include <base/action_bar/ActionBar.h>
#include <base/title_bar/TitleBar.h>
#include <base/selector/SelectorManager.h>
#include <base/content_manager/ContentManager.h>

#include "QuartzWindow.h"
#include "WelcomePage.h"
#include "HoverMoveFilter.h"
#include "adapted/CustomShadowEffect.h"

#define WINDOW_MARGIN 5


namespace Quartz {

QuartzWindow::QuartzWindow( QWidget *parent )
    : QMainWindow( parent )
    , m_chilliWidget( new QzMainWidget( this ))
    , m_moving( false )
    , m_maximised( false )
{
    this->setWindowFlags( Qt::FramelessWindowHint
                          | Qt::WindowMinimizeButtonHint );
    m_containerWidget = new QWidget( this );
    m_containerWidget->setContentsMargins( 5, 5, 5, 5 );
    setMouseTracking( true );
    setAttribute( Qt::WA_Hover );
    installEventFilter( new HoverMoveFilter( this ));

    m_chilliWidget->setContentsMargins( 5, 5, 0, 0 );
    m_layout = new QHBoxLayout( /*m_containerWidget*/ );
    m_layout->addWidget( m_chilliWidget );
    m_containerWidget->setAttribute( Qt::WA_TranslucentBackground, true );
    m_layout->setSpacing( 0 );
    m_layout->setContentsMargins( 5, 5, 0, 0 );
    m_containerWidget->setLayout( m_layout );

    CustomShadowEffect *effect = new CustomShadowEffect( this );
    effect->setBlurRadius( 10.0 );
    effect->setDistance( 3.0 );
    effect->setColor( QColor( 0xA0, 0x52, 0x2D, 0x80 ));
    m_chilliWidget->setGraphicsEffect( effect );

    this->setAttribute( Qt::WA_TranslucentBackground, true );
    this->setContentsMargins( QMargins() );
    this->setCentralWidget( m_containerWidget );

    //    QString color = style()->s
//    m_chilliWidget->setStyleSheet( "QWidget{background-color:white;}");
    connect( m_chilliWidget->titleBar(),
             SIGNAL( sigCloseRequested() ),
             this,
             SLOT( close() ));
    connect( m_chilliWidget->titleBar(),
             SIGNAL( sigMaxRestoreRequested() ),
             this,
             SLOT( onMaximizeRestore() ));
    connect( m_chilliWidget->titleBar() ,
             SIGNAL( sigMinimizeRequested() ),
             this,
             SLOT( onMinimize() ));
}


void QuartzWindow::onMinimize()
{
    minimize();
}


void QuartzWindow::onMaximizeRestore()
{
    if( m_maximised ) {
        m_maximised = false;
        restore();
    }
    else {
        m_geometry = saveGeometry();
        m_maximised = true;
        maximize();
    }
}


void QuartzWindow::mousePressEvent( QMouseEvent* event )
{
    if( event->button() == Qt::LeftButton ) {
        m_moving = true;
        if( m_cursorAtLeft ) {
            m_lastMousePosition.setX( event->pos().x() );
        }
        if( m_cursorAtRight ) {
            m_lastMousePosition.setX( width() - event->pos().x() );
        }
        if( m_cursorAtBottom ) {
            m_lastMousePosition.setY( height() - event->pos().y() );
        }
        else {
            m_lastMousePosition = event->globalPos();
        }
        QMainWindow::mousePressEvent( event );
    }
}


void QuartzWindow::mouseMoveEvent( QMouseEvent* event )
{
    if( event->buttons().testFlag( Qt::LeftButton )
            && m_moving
            && ! m_resizing ) {
        QPoint newPos = this->pos()
                + ( event->globalPos() - m_lastMousePosition );
        if( newPos.y() <= 0 ) {
            m_maximised = true;
            emit maximize();
        }
        else if( m_maximised && newPos.y() >= 10 ) {
            m_maximised = false;
            restore();
            move( event->globalX() - this->width() / 2, event->globalY() );
        }
        else {
            move( newPos );
        }
        m_lastMousePosition = event->globalPos();
    }
    QWidget::mouseMoveEvent( event );
}


void QuartzWindow::mouseReleaseEvent( QMouseEvent* event )
{
    if( event->button() == Qt::LeftButton ) {
        m_moving = false;
        m_resizing = false;
    }
    QWidget::mouseReleaseEvent( event );
}


void QuartzWindow::showEvent( QShowEvent *evt )
{
    if( m_geometry.isEmpty() ) {
        m_geometry = this->saveGeometry();
    }
    QWidget::showEvent( evt );
}


void QuartzWindow::resizeEvent( QResizeEvent *evt )
{
    QWidget::resizeEvent( evt );
}



void QuartzWindow::maximize()
{
    QDesktopWidget *desktop = QApplication::desktop();
    // Because reserved space can be on all sides of the scren
    // you have to both move and resize the window
    m_layout->setSpacing( 0 );
    m_layout->setContentsMargins( QMargins() );
    m_containerWidget->setContentsMargins( QMargins() );
    m_chilliWidget->setRoundedRect( false );

    QRect rect = desktop->availableGeometry(
                desktop->screenNumber(QCursor::pos()));
    this->setGeometry( rect );
}


void QuartzWindow::restore()
{
    if( ! m_geometry.isEmpty() ) {
        m_layout->setSpacing( 0 );
        m_layout->setContentsMargins( 5, 5, 0, 0 );
        m_containerWidget->setContentsMargins( 5, 5, 5, 5 );
        m_chilliWidget->setRoundedRect( true );
        this->restoreGeometry( m_geometry );
    }
}


void QuartzWindow::minimize()
{
    if( ! this->isMinimized() ) {
        this->showMinimized();
    }
}


void QuartzWindow::mouseMove( QPoint newPos, QPoint oldPos )
{
    if( m_moving ) {
        int dx = newPos.x() - oldPos.x();
        int dy = newPos.y() - oldPos.y();
        QRect g = geometry();
        QSize minSize = minimumSize();

        // We don't resize if the windows has the minimum size
        if( m_cursorAtLeft ) {
            // Fix a bug when you try to resize to less than minimum size and
            // then the mouse goes right again.
            if ( dx < 0 && oldPos.x() > m_lastMousePosition.x() ) {
                dx += oldPos.x() - m_lastMousePosition.x();
                if( dx > 0 ) {
                    dx = 0;
                }
            }
            else if( dx > 0 && g.width() - dx < minSize.width() ) {
                dx = g.width() - minSize.width();
            }
            g.setLeft( g.left() + dx );
        }
        if( m_cursorAtRight ) {
            // Fix a bug when you try to resize to less than minimum size and
            // then the mouse goes right again.
            if( dx > 0 && ( width() - newPos.x() > m_lastMousePosition.x() )) {
                dx -= width() - newPos.x() - m_lastMousePosition.x();
                if( dx < 0 ) {
                    dx = 0;
                }
            }
            g.setRight( g.right() + dx );
        }
        if( m_cursorAtBottom ) {
            // Fix a bug when you try to resize to less than minimum size and
            // then the mouse goes down again.
            if( dy > 0 && ( height() - newPos.y() > m_lastMousePosition.y() )) {
                dy -= height() - newPos.y() - m_lastMousePosition.y();
                if (dy < 0) {
                    dy = 0;
                }
            }
            g.setBottom( g.bottom() + dy );
        }
        setGeometry( g );

    } else {
        QRect r = rect();
        m_cursorAtLeft = ( qAbs( newPos.x()- r.left() ) <= WINDOW_MARGIN )
                && newPos.y() > m_chilliWidget->titleBar()->height();
        m_cursorAtRight = ( qAbs(newPos.x() - r.right()) <= WINDOW_MARGIN )
                && newPos.y() > m_chilliWidget->titleBar()->height();
        m_cursorAtBottom = ( qAbs( newPos.y() - r.bottom() ) <= WINDOW_MARGIN );
        bool horizontal = m_cursorAtLeft || m_cursorAtRight;

        m_resizing = true;
        if( horizontal && m_cursorAtBottom ) {
            if( m_cursorAtLeft ) {
                setCursor( Qt::SizeBDiagCursor );
            }
            else {
                setCursor( Qt::SizeFDiagCursor );
            }
        }
        else if( horizontal ) {
            setCursor( Qt::SizeHorCursor );
        }
        else if( m_cursorAtBottom ) {
            setCursor( Qt::SizeVerCursor );
        }
        else {
            setCursor( Qt::ArrowCursor );
            m_resizing = false;
        }
    }
}



//////////////////////////////////////////////////////////////////////////////
QzMainWidget::QzMainWidget( QMainWindow *parent )
    : QWidget( parent )
    , m_roundedRect( true )
    , m_titleBar( new TitleBar( 60, this ) )
    , m_selector( new SelectorManager( 60, 60, this ))
    , m_content( new ContentManager( this ))
    , m_actionBar( new ActionBar( 60, this ))
{
    this->setObjectName( "chillimain" );
//    m_titleBar = new TitleBar( 20, this );
//    m_actionBar = new ActionBar( 20, this );
//    m_pageManager = new PageManager( 60, 20, this );
//    m_viewManager = new ViewManager( 20, 60, this );
//    auto page = new WelcomePage( this );
//    auto apage = new AnotherPage( this );
//    m_pageManager->addPage( page );
//    m_pageManager->addPage( apage );
//    m_sizeGrip = new QSizeGrip( this );
//    m_sizeGrip->setContentsMargins( QMargins() );
//    mainLayout->addWidget( m_sizeGrip, 0, Qt::AlignBottom | Qt::AlignRight );

    QVBoxLayout *mainLayout = new QVBoxLayout();

    QWidget *middle = new QWidget{ this };
    QHBoxLayout *middleLayout = new QHBoxLayout{ };
    middleLayout->addWidget( m_selector );
    middleLayout->addWidget( m_content );
    middle->setLayout( middleLayout );

    mainLayout->addWidget( m_titleBar );
    mainLayout->setAlignment( m_titleBar, Qt::AlignTop );
    mainLayout->addWidget( middle );
    mainLayout->addWidget( m_actionBar);
    mainLayout->setAlignment( m_actionBar, Qt::AlignBottom );
    mainLayout->setContentsMargins( QMargins( 0, 0, 3, 3 ));
    this->setLayout( mainLayout );
    this->setStyleSheet( "border-color: red;");

//    auto page = new WelcomePage( this );
//    auto apage = new AnotherPage( this );
}


TitleBar * QzMainWidget::titleBar()
{
    return m_titleBar;
}


void QzMainWidget::onAboutToQuit()
{

}


void QzMainWidget::paintEvent( QPaintEvent * /*event*/ )
{
    QPainter painter( this );
    auto color = this->palette().color( QPalette::Background );
    if( m_roundedRect ) {
        QPainterPath path;
        path.addRoundedRect( this->rect(), 5, 5 );
        QBrush brush( color );
        painter.setRenderHint( QPainter::Antialiasing );
        painter.setRenderHint( QPainter::HighQualityAntialiasing );
        painter.fillPath( path, brush );
    }
    else {
        painter.fillRect( this->rect(), QBrush( color ));
    }
}


}
