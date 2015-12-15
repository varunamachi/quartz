
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QApplication>
#include <QPainter>

#include "QuartzWindow.h"
#include "WelcomePage.h"
#include "adapted/CustomShadowEffect.h"


namespace Vam { namespace Quartz {

QuartzWindow::QuartzWindow( QWidget *parent )
    : QMainWindow( parent )
    , m_chilliWidget( new QzMainWidget( this ))
    , m_maximised( false )
{
    this->setWindowFlags( Qt::FramelessWindowHint
                          | Qt::WindowMinimizeButtonHint );
    m_containerWidget = new QWidget( this );
    m_containerWidget->setContentsMargins( 5, 5, 5, 5 );


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
        m_lastMousePosition = event->globalPos();
    }
}

void QuartzWindow::mouseMoveEvent( QMouseEvent* event )
{
    if( event->buttons().testFlag( Qt::LeftButton ) && m_moving ) {
        QPoint newPos = this->pos() + (
                    event->globalPos() - m_lastMousePosition );
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
}


void QuartzWindow::mouseReleaseEvent( QMouseEvent* event )
{
    if( event->button() == Qt::LeftButton )
    {
        m_moving = false;
    }
}


void QuartzWindow::showEvent( QShowEvent *evt )
{
    if( m_geometry.isEmpty() ) {
        m_geometry = this->saveGeometry();
    }
    QWidget::showEvent( evt );
}


void QuartzWindow::resizeEvent( QResizeEvent * )
{

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
    this->setGeometry( desktop->availableGeometry() );
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



//////////////////////////////////////////////////////////////////////////////
QzMainWidget::QzMainWidget( QMainWindow *parent )
    : QWidget( parent )
    , m_roundedRect( true )
{

    this->setObjectName( "chillimain" );


    m_titleBar = new TitleBar( 20, this );
    m_pageManager = new PageManager( 60, 20, this );
    m_viewManager = new ViewManager( 20, 60, this );
    m_actionBar = new ActionBar( 20, this );
    auto page = new WelcomePage( this );
    m_pageManager->addPage( page );

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget( m_titleBar );
    mainLayout->setAlignment( m_titleBar, Qt::AlignTop );
    mainLayout->addWidget( m_pageManager );
    mainLayout->addWidget( m_viewManager );
    mainLayout->setAlignment( m_viewManager, Qt::AlignBottom );
    mainLayout->addWidget( m_actionBar);
    mainLayout->setAlignment( m_actionBar, Qt::AlignBottom );
    mainLayout->setContentsMargins( QMargins() );
    m_sizeGrip = new QSizeGrip( this );
    m_sizeGrip->setContentsMargins( QMargins() );
    mainLayout->addWidget( m_sizeGrip, 0, Qt::AlignBottom | Qt::AlignRight );
    this->setLayout( mainLayout );
}



void QzMainWidget::onAboutToQuit()
{
}


void QzMainWidget::paintEvent( QPaintEvent */*event*/ )
{
    QPainter painter( this );
    if( m_roundedRect ) {
        QPainterPath path;
        path.addRoundedRect( this->rect(), 10, 10 );
        QBrush brush( Qt::white );
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::HighQualityAntialiasing);
        painter.fillPath( path, brush );
    }
    else {
        painter.fillRect( this->rect(), QBrush( Qt::white ));
    }
}


} }
