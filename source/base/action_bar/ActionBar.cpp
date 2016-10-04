#include <QPushButton>
#include <QHBoxLayout>

#include <common/widgets/QzScroller.h>

#include "../title_bar/QuartzItem.h"
#include "ActionBar.h"

namespace Quartz {

const QString ActionBar::ADAPTER_NAME { "action_bar" };
const QString ActionBar::PLUGIN_TYPE { "action_bar_item" };


ActionBar::ActionBar( int height, QWidget *parent )
    : QWidget( parent )
    , m_height( height )

{
    m_scroller = new QzScroller( Qt::Horizontal, height, height, this );
    m_scroller->setContentsMargins( QMargins() );
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins( QMargins() );
//    layout->addStretch();
    layout->addWidget( m_scroller );
    this->setContentsMargins( QMargins() );
    this->setLayout( layout );
//    this->setStyleSheet("QWidget{background-color:red;}");
}


void ActionBar::addItem( QuartzItem *item )
{
    if( item != nullptr ) {
        m_items.insert( item->itemId(), item );
        m_scroller->addWidget( item );
    }
}


void ActionBar::removeItem( QuartzItem *item )
{
    if( item != nullptr && m_items.contains( item->itemId() )) {
        m_items.remove( item->itemId() );
        m_scroller->removeWidget( item );
        delete item;
    }
}


void ActionBar::removeItem( const QString &itemId )
{
    QuartzItem *item = m_items.value( itemId );
    if( item != nullptr ) {
        m_items.remove( itemId );
        m_scroller->removeWidget( item );
        delete item;
    }
}


QList< QuartzItem * > ActionBar::items() const
{
    return m_items.values();
}


QList< QuartzItem * > ActionBar::items( const QString category )
{
    QList< QuartzItem *> filteredItems;
    for( QuartzItem *item : m_items.values() ) {
        if( item->itemCategory() == category ) {
            filteredItems.append( item );
        }
    }
    return filteredItems;
}


void ActionBar::removeCategory( const QString &category )
{
    QList< QuartzItem * > itemList = items( category );
    for( QuartzItem *item : itemList ) {
        removeItem( item );
    }
}

const QString & ActionBar::pluginType() const
{
    return PLUGIN_TYPE;
}

const QString & ActionBar::pluginAdapterName() const
{
    return ADAPTER_NAME;
}

bool ActionBar::handlePlugin( IPlugin *plugin )
{

}

bool ActionBar::finalizePlugins()
{

}


}





