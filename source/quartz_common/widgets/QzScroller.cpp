
#include <QScrollArea>
#include <QBoxLayout>
#include <QScrollBar>
#include <QComboBox>
#include <QPushButton>
#include <QTimer>
#include <QDebug>

#include "QzScroller.h"

namespace Vq { namespace Quartz {

QzScroller::QzScroller( Qt::Orientation orientation,
                        int minimumDim,
                        int maximumDim,
                        QWidget *parent )
    : QWidget( parent )
    , m_orientation( orientation )
    , m_bckButton( new QPushButton( "<", this ))
    , m_fwdButton( new QPushButton( ">", this ))
    , m_timer( new QTimer( this ))
    , m_timeout( 0 )
{
    m_scroll = new QScrollArea( this );
    m_scroll->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    m_scroll->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    m_scroll->setWidgetResizable( true );
    m_scroll->setContentsMargins( QMargins() );
    m_scroll->setStyleSheet( "QScrollArea{ border: 0px; }");
    QWidget *innerWidget = new QWidget( this );
    if( orientation == Qt::Horizontal ) {
        m_layout = new QHBoxLayout();
        m_scroll->setMaximumHeight( maximumDim );
        m_scroll->setMinimumHeight( minimumDim );
    }
    else {
        m_layout = new QVBoxLayout();
        m_scroll->setMaximumWidth( maximumDim );
        m_scroll->setMinimumWidth( minimumDim );
    }
    m_layout->setContentsMargins( QMargins() );
    m_layout->setMargin( 0 );
    m_layout->addStretch( 0 );
    m_layout->setSizeConstraint( QLayout::SetMinAndMaxSize );
    innerWidget->setLayout( m_layout );
    innerWidget->setContentsMargins( QMargins() );
    innerWidget->setMinimumSize( QSize( maximumDim, 20 ));
    m_fwdButton->setFlat( true );
    m_bckButton->setFlat( true );
    m_fwdButton->setVisible( false );
    m_bckButton->setVisible( false );

//    QStringList items;
//    items << "One" << "Two" << "Three" << "Four";
//    for( int i = 0; i < 10; ++ i ) {
//        QComboBox *box = new QComboBox( innerWidget );
//        box->addItems( items );
//        m_layout->addWidget( box );
//    }

    m_bckButton->setMaximumWidth( 20 );
    m_fwdButton->setMaximumWidth( 20 );
    m_bckButton->setMaximumHeight( 20 );
    m_fwdButton->setMaximumHeight( 20 );


    m_scroll->setWidget( innerWidget );
    QBoxLayout *mainLayout = nullptr;
    if( orientation == Qt::Horizontal ) {
        mainLayout = new QHBoxLayout();
        mainLayout->addWidget( m_bckButton );
        mainLayout->setAlignment( m_bckButton, Qt::AlignLeft );
        mainLayout->addWidget( m_scroll );
        mainLayout->addWidget( m_fwdButton );
        mainLayout->setAlignment( m_fwdButton, Qt::AlignRight );
    }
    else {
        mainLayout = new QVBoxLayout();
        mainLayout->addWidget( m_bckButton );
        mainLayout->setAlignment( m_bckButton, Qt::AlignTop);
        mainLayout->addWidget( m_scroll );
        mainLayout->addWidget( m_fwdButton );
        mainLayout->setAlignment( m_fwdButton, Qt::AlignBottom );
    }
    mainLayout->setContentsMargins( QMargins() );
    this->setLayout( mainLayout );

    connect( m_fwdButton,
             &QAbstractButton::pressed,
             this,
             &QzScroller::start );
    connect( m_fwdButton,
             &QAbstractButton::released,
             this,
             &QzScroller::stop );
    connect( m_bckButton,
             &QAbstractButton::pressed,
             this,
             &QzScroller::start);
    connect( m_bckButton,
             &QAbstractButton::released,
             this,
             &QzScroller::stop );
    connect( m_timer,
             &QTimer::timeout,
             this,
             &QzScroller::onTimeout );

}


QWidgetList QzScroller::widgets() const
{
    QWidgetList widgets;
    for( int i = 0; i < m_layout->count(); ++ i ) {
        QLayoutItem *item = m_layout->itemAt( i );
        QWidget *widget = item->widget();
        if( widget != nullptr ) {
            widgets.append( widget );
        }
    }
    return widgets;
}


void QzScroller::addWidget( QWidget *widget )
{
    if( widget != nullptr ) {
        m_layout->insertWidget( m_layout->count() - 1, widget );
        adjustArrows();
    }
}


void QzScroller::removeWidget( QWidget *widget )
{
    if( widget != nullptr ) {
        m_layout->removeWidget( widget );
        adjustArrows();
    }
}

void QzScroller::resizeEvent(QResizeEvent *event)
{
    adjustArrows();
    QWidget::resizeEvent(event);
}



void QzScroller::start()
{
    m_timeout = 100;
    onTimeout();
}


void QzScroller::stop()
{
    m_timer->stop();
}


void QzScroller::onTimeout()
{
    if( m_timeout > 10 ) {
        m_timer->start( m_timeout );
        m_timeout = m_timeout - 10;
    }
    QScrollBar *bar = m_orientation == Qt::Horizontal
            ? m_scroll->horizontalScrollBar()
            : m_scroll->verticalScrollBar();
    int val = bar->value();
    if( m_fwdButton->isDown() ) {
        bar->setValue( val + 8 );
    }
    else if( m_bckButton->isDown() ){
        bar->setValue( val - 8 );
    }
}


void QzScroller::adjustArrows()
{
    int occupied = 0;
    for( int i = 0; i < m_layout->count(); ++ i ) {
        QLayoutItem *item = m_layout->itemAt( i );
        QRect rect = item->geometry();
        if( m_orientation == Qt::Horizontal ) {
            occupied += rect.width();
        }
        else {
            occupied += rect.height();
        }
    }
    if( m_orientation == Qt::Horizontal && occupied > this->width() ) {
        m_fwdButton->setVisible( true );
        m_bckButton->setVisible( true );
    }
    else if( m_orientation == Qt::Vertical && occupied > this->height() ) {
        m_fwdButton->setVisible( true );
        m_bckButton->setVisible( true );
    }
    else {
        m_fwdButton->setVisible( false );
        m_bckButton->setVisible( false );
    }
    m_layout->update();
}


} }
