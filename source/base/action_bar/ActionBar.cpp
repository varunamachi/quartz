#include <QPushButton>
#include <QHBoxLayout>

#include <common/widgets/QzScroller.h>

#include "../title_bar/QuartzItem.h"
#include "AbstractActionItemProvider.h"
#include "ActionBar.h"


namespace Quartz {

const QString ActionBar::ADAPTER_NAME { "action_bar" };


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
    return  AbstractActionItemProvider::PLUGIN_TYPE;
}

const QString & ActionBar::pluginAdapterName() const
{
    return ADAPTER_NAME;
}

bool ActionBar::handlePlugin( IPlugin *plugin )
{
    auto itemProvider = dynamic_cast< AbstractActionItemProvider *>( plugin );
    if( itemProvider != nullptr ) {
        auto item = itemProvider->actionItem();
        addItem( item );
        m_pluginItems.push_back( item );
        return true;
    }
    return false;
}

bool ActionBar::finalizePlugins()
{
    for( int i = 0; i < m_pluginItems.size(); ++ i ) {
        auto item = m_pluginItems.at( i );
        removeItem( item );
    }
    return  true;
}


}





