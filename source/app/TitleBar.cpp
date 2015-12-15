#include <QPushButton>
#include <QHBoxLayout>

#include "TitleBar.h"

namespace Vam { namespace Quartz {


TitleBar::TitleBar( int height, QWidget *parent )
    : QWidget( parent )
    , m_height( height )

{
    m_scroller = new QzScroller( Qt::Horizontal, height, height, this );
    m_minimizeBtn = new QPushButton( "_", this );
    m_maxRestoreBtn = new QPushButton( "[]", this );
    m_closeBtn = new QPushButton( "X", this );

    m_scroller->setContentsMargins( QMargins() );
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins( QMargins() );
//    layout->addStretch();
    layout->addWidget( m_scroller );
    layout->addWidget( m_minimizeBtn );
    layout->addWidget( m_maxRestoreBtn );
    layout->addWidget( m_closeBtn );
    m_minimizeBtn->setMaximumSize( 20, 20 );
    m_maxRestoreBtn->setMaximumSize( 20, 20 );
    m_closeBtn->setMaximumSize( 20, 20 );
    m_minimizeBtn->setMinimumSize( 20, 20 );
    m_maxRestoreBtn->setMinimumSize( 20, 20 );
    m_closeBtn->setMinimumSize( 20, 20 );
    this->setContentsMargins( QMargins() );
    this->setLayout( layout );

}

void TitleBar::addItem( QuartzItem *item )
{
    if( item != nullptr ) {
        m_items.insert( item->itemId(), item );
        m_scroller->addWidget( item );
    }
}


void TitleBar::removeItem( QuartzItem *item )
{
    if( item != nullptr && m_items.contains( item->itemId() )) {
        m_items.remove( item->itemId() );
        m_scroller->removeWidget( item );
        delete item;
    }
}


void TitleBar::removeItem( const QString &itemId )
{
    QuartzItem *item = m_items.value( itemId );
    if( item != nullptr ) {
        m_items.remove( itemId );
        m_scroller->removeWidget( item );
        delete item;
    }
}


QList< QuartzItem * > TitleBar::items() const
{
    return m_items.values();
}


QList< QuartzItem * > TitleBar::items( const QString category )
{
    QList< QuartzItem *> filteredItems;
    for( QuartzItem *item : m_items.values() ) {
        if( item->itemCategory() == category ) {
            filteredItems.append( item );
        }
    }
    return filteredItems;
}


void TitleBar::removeCategory( const QString &category )
{
    QList< QuartzItem * > itemList = items( category );
    for( QuartzItem *item : itemList ) {
        removeItem( item );
    }
}

} }
