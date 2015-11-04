
#include "StackedContainer.h"

namespace Vam { namespace Quartz {

StackedContainer::StackedContainer( int selectorDimention,
                                    Qt::Orientation orientation,
                                    QWidget *parent = nullptr )
    : QWidget( parent )
    , m_selector( new QzScroller( orientation,
                                  selectorDimention,
                                  selectorDimention,
                                  this ))
    , m_stackWidget( new QStackedWidget( this ))
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget( m_selector );
    layout->addWidget( m_stackWidget );
    layout->setContentsMargins( QMargins() );
    m_selector->setContentsMargins( QMargins() );
    m_stackWidget->setContentsMargins( QMargins() );
    this->setLayout( layout );
}

QWidget *StackedContainer::widget( const QString &id ) const
{
    QWidget *widget = m_widgets.value( id );
    return widget;
}


QString StackedContainer::currentId() const
{
    return m_selectedId;
}


QList< QString > StackedContainer::allIds() const
{
    return m_widgets.keys();
}


void StackedContainer::addWidget( QString id, QWidget *widget )
{
}


void StackedContainer::removeWidget( QString id )
{

}


void StackedContainer::removeWidget( QWidget widget )
{

}


void StackedContainer::select( QString id )
{

}


void StackedContainer::onSelected(QString &id)
{

}

} }
