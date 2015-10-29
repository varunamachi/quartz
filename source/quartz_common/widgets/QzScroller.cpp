
#include <QScrollArea>
#include <QBoxLayout>
#include <QScrollBar>
#include <QComboBox>
#include <QPushButton>
#include <QTimer>
#include <QDebug>

#include "QzScroller.h"

namespace Vam { namespace Quartz {

QzScroller::QzScroller( Qt::Orientation orientation, QWidget *parent )
    : QWidget( parent )
    , m_orientation( orientation )
    , m_bckButton( new QPushButton( "<<", this ))
    , m_fwdButton( new QPushButton( ">>", this ))
    , m_timer( new QTimer( this ))
    , m_timeout( 0 )
{
    QWidget *innerWidget = new QWidget( this );
    if( orientation == Qt::Horizontal ) {
        m_layout = new QHBoxLayout();
    }
    else {
        m_layout = new QVBoxLayout();
    }
    innerWidget->setLayout( m_layout );
    m_layout->setContentsMargins( QMargins() );
    innerWidget->setContentsMargins( QMargins() );
    m_layout->setMargin( 0 );
    m_layout->setSizeConstraint( QLayout::SetMinAndMaxSize );
    innerWidget->setMinimumSize( QSize( 100, 20 ));

    QStringList items;
    items << "One" << "Two" << "Three" << "Four";
    for( int i = 0; i < 10; ++ i ) {
        QComboBox *box = new QComboBox( innerWidget );
        box->addItems( items );
        m_layout->addWidget( box );
    }

    m_scroll = new QScrollArea( this );
    m_scroll->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    m_scroll->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    m_scroll->setWidget( innerWidget );

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget( m_bckButton );
    mainLayout->addWidget( m_scroll );
    mainLayout->addWidget( m_fwdButton );
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


void QzScroller::start()
{
//    auto bar = m_scroll->horizontalScrollBar();
//    bar->setValue( bar->value() - 5 );
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
    QScrollBar *bar = m_scroll->horizontalScrollBar();
    if( m_fwdButton->isDown() ) {
        bar->setValue( bar->value() - 5 );
    }
    else if( m_bckButton->isDown() ){
        bar->setValue( bar->value() + 5 );
    }
}


} }
