
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QApplication>
#include <QPainter>

#include "QuartzWindow.h"
#include "adapted/CustomShadowEffect.h"

namespace Vam { namespace Quartz {

QuartzWindow::QuartzWindow( QWidget *parent )
    : QMainWindow( parent )
    , m_chilliWidget( new ChilliMainWidget( this ))
    , m_maximised( false )
{
    this->setWindowFlags( Qt::FramelessWindowHint
                          | Qt::WindowMinimizeButtonHint );
    m_containerWidget = new QWidget( this );
    m_containerWidget->setContentsMargins( 5, 5, 5, 5 );


    m_chilliWidget->setContentsMargins( 5, 5, 0, 0 );
    m_layout = new QHBoxLayout( m_containerWidget );
    m_layout->addWidget( m_chilliWidget );
    m_containerWidget->setAttribute( Qt::WA_TranslucentBackground, true );
    this->setAttribute( Qt::WA_TranslucentBackground, true );
    this->setCentralWidget( m_containerWidget );
    m_layout->setSpacing( 0 );
    m_layout->setContentsMargins( 5, 5, 0, 0 );

    CustomShadowEffect *effect = new CustomShadowEffect( this );
    effect->setBlurRadius( 10.0 );
    effect->setDistance( 3.0 );
    effect->setColor( QColor( 0xA0, 0x52, 0x2D, 0x80 ));
    m_chilliWidget->setGraphicsEffect( effect );
//    connect( m_chilliWidget->m_audioPlayer,
//             SIGNAL( exit() ),
//             QApplication::instance(),
//             SLOT( quit() ));
//    connect( m_chilliWidget->m_audioPlayer,
//             SIGNAL( minimize() ),
//             this,
//             SLOT( onMinimize() ));
    this->setContentsMargins( QMargins() );
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


void QuartzWindow::resizeEvent( QResizeEvent */*evt*/ )
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
ChilliMainWidget::ChilliMainWidget( QWidget *parent )
    : QWidget( parent )
    , m_roundedRect( true )
{

    this->setObjectName( "chillimain" );

//    QHBoxLayout *topLayout = new QHBoxLayout();
//    m_audioPlayer = new AudioPlayerWidget( this );

//    m_playlist = new PlaylistWidget( this );
//    m_audioPlayer->setContentsMargins( QMargins( 2, 2, 2, 2 ));
//    m_playlist->setContentsMargins( QMargins( 2, 2, 2, 0 ));
//    ComponentManager::get()->setContentsMargins( QMargins( 2, 2, 2, 0 ));

//    QHBoxLayout *bottomLyt = new QHBoxLayout();
//    bottomLyt->addWidget( m_playlist );
//    bottomLyt->addWidget( ComponentManager::get() );
//    bottomLyt->setContentsMargins( QMargins() );
//    bottomLyt->setSpacing( 0 );

//    auto *layout = new QVBoxLayout();
//    layout->addWidget( m_audioPlayer );
//    layout->addLayout( bottomLyt );
//    layout->setContentsMargins( QMargins() );
//    layout->setSpacing( 0 );


//    m_sizeGrip = new QSizeGrip( this );
//    m_sizeGrip->setContentsMargins( QMargins() );
//    layout->addWidget( m_sizeGrip, 0, Qt::AlignBottom | Qt::AlignRight );

//    this->setLayout( layout );
////    m_si new QSizeGrip( this );

//    QString css = createStyleSheet();
//    ComponentManager::get()->setStyleSheet( css );
//    m_playlist->setStyleSheet( css );
//    m_audioPlayer->setStyleSheet( css );

//    connect( m_audioPlayer, SIGNAL( urlsDropped( QList< QUrl > )),
//             m_playlist, SLOT( addUrls( QList< QUrl > )));
//    connect( m_audioPlayer, SIGNAL( playFromPlaylist() ),
//             m_playlist, SLOT( setSelectedAsCurrent() ));
//    connect( QCoreApplication::instance(),
//             SIGNAL( aboutToQuit() ),
//             this,
//             SLOT( onAboutToQuit() ));
}



void ChilliMainWidget::onAboutToQuit()
{
//    while( JOB_MANAGER()->hasPendingJobs() ) {
//        QThread::currentThread()->sleep( 1 );
//    }
//    const QList< Tanyatu::Data::MediaItem *> *list =
//            PLAYQUEUE()->getAllItemsInOrder();
//    DATA_UPDATER()->saveCurrentPlaylist( *list );
//    ComponentManager::destroy();
//    CHILLI_CACHE()->destroy();
}


void ChilliMainWidget::paintEvent( QPaintEvent */*event*/ )
{
    QPainter painter( this );
    if( m_roundedRect ) {
        QPainterPath path;
        path.addRoundedRect( this->rect(), 10, 10 );
        QBrush brush( Qt::black );
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::HighQualityAntialiasing);
        painter.fillPath( path, brush );
    }
    else {
        painter.fillRect( this->rect(), QBrush( Qt::black ));
    }
}


} }
