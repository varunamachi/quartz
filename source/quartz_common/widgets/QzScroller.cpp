
#include <QScrollArea>
#include <QBoxLayout>
#include <QScrollBar>
#include <QComboBox>

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
    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget( m_scroll );
    this->setLayout( mainLayout );


}



} }
