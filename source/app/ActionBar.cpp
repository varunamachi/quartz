
#include <QHBoxLayout>
#include <QLabel>

#include "ActionBar.h"

namespace Vam { namespace Quartz {

ActionBar::ActionBar( int height, QWidget *parent )
    : QWidget( parent )
    , m_height( height )
{
    m_layout = new QHBoxLayout();
    this->setLayout( m_layout );
}


void ActionBar::addItem( QuartzItem *widget )
{

}


void ActionBar::removeItem( QuartzItem *widget )
{

}


void ActionBar::removeItem( const QString &itemId )
{

}


void ActionBar::removeCategory( const QString &category )
{

}


QList< QuartzItem * > ActionBar::items() const
{
    QList< QuartzItem * > list;
    return list;
}


QList< QuartzItem * > ActionBar::items( const QString category )
{
    QList< QuartzItem * > items;
    return items;
}



} }

