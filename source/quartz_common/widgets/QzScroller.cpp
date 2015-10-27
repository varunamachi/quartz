
#include <QScrollArea>
#include <QBoxLayout>
#include <QScrollBar>
#include <QComboBox>
#include <QPushButton>

#include "QzScroller.h"

namespace Vam { namespace Quartz {

QzScroller::QzScroller( Qt::Orientation orientation, QWidget *parent )
    : QWidget( parent )
    , m_orientation( orientation )
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

    m_scroll = new QScrollArea( /*this*/ );
    m_scroll->horizontalScrollBar()->hide();
    m_scroll->verticalScrollBar()->hide();
    m_scroll->setWidget( innerWidget );

    QPushButton *bckButton = new QPushButton( "<<", this );
    QPushButton *fwdButton = new QPushButton( ">>", this );

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget( bckButton );
    mainLayout->addWidget( m_scroll );
    mainLayout->addWidget( fwdButton );
    mainLayout->setContentsMargins( QMargins() );
    this->setLayout( mainLayout );

    connect( bckButton,
             SIGNAL( clicked( bool )),
             this,
             SLOT( whenBackward() ));
    connect( fwdButton,
             SIGNAL( clicked( bool )),
             this,
             SLOT( whenForward() ));

}


void QzScroller::whenForward()
{
    m_scroll->scroll( -5, 0 );
}


void QzScroller::whenBackward()
{
    m_scroll->scroll( +5, 0 );
}



} }
