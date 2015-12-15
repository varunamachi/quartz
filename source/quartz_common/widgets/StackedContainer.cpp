#include <QVariant>
#include <QMouseEvent>

#include "StackedContainer.h"

namespace Vam { namespace Quartz {


StackedContainer::StackedContainer( int selectorDimention,
                                    int buttonDimention,
                                    Qt::Orientation orientation,
                                    QWidget *parent )
    : QWidget( parent )
    , m_selector( new QzScroller( orientation,
                                  selectorDimention,
                                  selectorDimention,
                                  this ))
    , m_stackWidget( new QStackedWidget( this ))
{
    QBoxLayout *layout = nullptr;
    if( orientation == Qt::Vertical ) {
        layout = new QHBoxLayout();
        m_selector->setMaximumWidth( selectorDimention );
        m_selector->setMinimumWidth( selectorDimention );
        m_btnWidth = selectorDimention;
        m_btnHeight = buttonDimention;
    }
    else {
        layout = new QVBoxLayout();
        m_selector->setMaximumHeight( selectorDimention );
        m_selector->setMinimumHeight( selectorDimention );
        m_btnWidth = buttonDimention;
        m_btnHeight = selectorDimention;
    }
    layout->addWidget( m_selector );
    layout->addWidget( m_stackWidget );
    layout->setContentsMargins( QMargins() );
    m_selector->setContentsMargins( QMargins() );
    m_stackWidget->setContentsMargins( QMargins() );
//    m_selector->setStyleSheet("background-color: blue;");
//    m_stackWidget->setStyleSheet("background-color: red;");
    this->setLayout( layout );
}


QWidget * StackedContainer::widget( const QString &id ) const
{
//    QWidget *widget = m_widgets.value( id );
//    return widget;
    QWidget *widget = nullptr;
    Item::Ptr item = m_items.value( id );
    if( item ) {
        widget = item->m_widget;
    }
    return widget;
}


QString StackedContainer::currentId() const
{
    return m_selectedId;
}


QList< QString > StackedContainer::allIds() const
{
    return m_items.keys();
}


void StackedContainer::addWidget( const QString &id,
                                  const QString &displayName,
                                  QWidget *widget )
{
    if( widget != nullptr ) {
        IdButton *btn = new IdButton( id,
                                      displayName,
                                      m_btnHeight,
                                      m_btnWidth,
                                      this );
        int index = m_stackWidget->addWidget( widget );
        Item::Ptr item = Item::create( index, btn, widget );
        m_items.insert( id, item );
        m_selectedId = id;
        m_selector->addWidget( btn );
        m_stackWidget->addWidget( widget );
        m_stackWidget->setCurrentIndex( index );
        btn->setChecked( true );
        widget->setProperty( "item_id", id );
    }
}


void StackedContainer::removeWidget( const QString &id )
{
    Item::Ptr item = m_items.value( id );
    if( item ) {
        QWidget *theWidget = widget( id );
        m_selector->removeWidget( item->m_btn );
        m_stackWidget->removeWidget( item->m_widget );
        m_items.remove( id );
        if( m_selectedId == id ) {
            m_selectedId = m_items.isEmpty()
                    ? ""
                    : m_items.begin().key();
        }
        updateIndeces();
        theWidget->setProperty( "item_id", QVariant() );
    }
}


void StackedContainer::removeWidget( QWidget *widget )
{
    for( auto it = m_items.begin(); it != m_items.end(); ++ it ) {
        Item::Ptr item = it.value();
        if( item->m_widget == widget ) {
            removeWidget( it.key() );
            /* I am not breaking here because same widget might have been added
             * multiple times. If later if we find it not important we can break
             * here.
             */
        }
    }
}


void StackedContainer::select( const QString &id )
{
    Item::Ptr item = m_items.value( id );
    if( item ) {
        m_stackWidget->setCurrentIndex( item->m_index );
    }
}


void StackedContainer::updateIndeces()
{
    for( int i = 0; i < m_stackWidget->count() && i < m_items.size() ; ++ i ) {
        QWidget *widget = m_stackWidget->widget( i );
        QVariant itemId = widget->property( "item_id" );
        if( itemId.isValid() ) {
            QString id = itemId.toString();
            Item::Ptr item = m_items.value( id );
            item->m_index = i;
        }
    }
}


int StackedContainer::numWidgets() const
{
    return m_items.size();
}


bool StackedContainer::isEmpty()
{
    return m_items.isEmpty();
}

} }
