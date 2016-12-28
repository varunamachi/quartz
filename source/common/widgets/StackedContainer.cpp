#include <QVariant>
#include <QMouseEvent>

#include "StackedContainer.h"

namespace Quartz {

struct Item {
    using Ptr = std::shared_ptr< Item >;

    IdButton *m_btn;

    QWidget *m_widget;

    int m_index;

    inline Item( int index, IdButton *btn, QWidget *widget )
        : m_index( index )
        , m_btn( btn )
        , m_widget( widget )
    {

    }

    static inline Item::Ptr create( int index,
                                    IdButton *btn,
                                    QWidget *widget )
    {
        return std::make_shared< Item >( index, btn, widget );
    }
};

struct AbstractContainer::Data
{
    Data( int selectorDimention,
          int buttonDimention,
          SelectorPosition selectorPosition,
          Qt::Orientation orientation,
          Qt::Orientation btnOriantation,
          QzScroller *scroller,
          QStackedWidget *stackedWidget )
        : m_btnHeight( selectorDimention )
        , m_btnWidth( buttonDimention )
        , m_selectorPosition( selectorPosition )
        , m_orientation( orientation )
        , m_btnOrientation( btnOriantation )
        , m_selector( scroller )
        , m_stackWidget( stackedWidget )
    {

    }

    int m_btnHeight;

    int m_btnWidth;

    SelectorPosition m_selectorPosition;

    Qt::Orientation m_orientation;

    Qt::Orientation m_btnOrientation;

    QzScroller *m_selector;

    QStackedWidget *m_stackWidget;

    QString m_selectedId;

    QHash< QString, Item::Ptr > m_items;
};


AbstractContainer::AbstractContainer( int selectorDimention,
                                    int buttonDimention,
                                    SelectorPosition selectorPosition,
                                    Qt::Orientation orientation,
                                    Qt::Orientation btnOrientation,
                                    QWidget *parent )
    : QWidget( parent )
    , m_data( new Data{
              selectorDimention,
              buttonDimention,
              selectorPosition,
              orientation,
              btnOrientation,
              new QzScroller{ orientation,
                              selectorDimention,
                              selectorDimention,
                              this },
              new QStackedWidget{ this }})
{
    if( btnOrientation == orientation ) {
        if( btnOrientation == Qt::Horizontal ) {
            m_data->m_btnWidth  = buttonDimention;
            m_data->m_btnHeight = selectorDimention;
            m_data->m_selector->setMaximumHeight( selectorDimention );
        }
        else {
            m_data->m_btnWidth = selectorDimention;
            m_data->m_btnHeight = buttonDimention;
            m_data->m_selector->setMaximumWidth( selectorDimention );
        }
    }
    else {
        if( btnOrientation == Qt::Horizontal ) {
            m_data->m_btnWidth = selectorDimention;
            m_data->m_btnHeight = buttonDimention;
            m_data->m_selector->setMaximumWidth( selectorDimention );
        }
        else {
            m_data->m_btnWidth  = buttonDimention;
            m_data->m_btnHeight = selectorDimention;
            m_data->m_selector->setMaximumHeight( selectorDimention );
        }
    }
    m_data->m_selector->setContentsMargins( QMargins() );
    m_data->m_stackWidget->setContentsMargins( QMargins() );
    this->setContentsMargins( QMargins{ });
}

AbstractContainer::~AbstractContainer()
{

}


QWidget * AbstractContainer::widget( const QString &id ) const
{
    QWidget *widget = nullptr;
    auto item = m_data->m_items.value( id );
    if( item ) {
        widget = item->m_widget;
    }
    return widget;
}

QWidget *AbstractContainer::selectedWidget() const
{
    QWidget *selected = nullptr;
    auto item = m_data->m_items.value( m_data->m_selectedId );
    if( item != nullptr ) {
        selected = item->m_widget;
    }
    return selected;
}


QString AbstractContainer::currentId() const
{
    return m_data->m_selectedId;
}


QList< QString > AbstractContainer::allIds() const
{
    return m_data->m_items.keys();
}


void AbstractContainer::addWidget( const QString &id,
                                  const QString &displayName,
                                  QWidget *widget )
{
    if( widget != nullptr ) {
        auto *btn = new IdButton( id,
                                  displayName,
                                  m_data->m_btnHeight,
                                  m_data->m_btnWidth,
                                  this,
                                  m_data->m_btnOrientation );
        btn->setContentsMargins( QMargins{ });
        auto index = m_data->m_stackWidget->addWidget( widget );
        auto item = Item::create( index, btn, widget );
        m_data->m_items.insert( id, item );
        m_data->m_selector->addWidget( btn );
        m_data->m_stackWidget->addWidget( widget );
        connect( btn,
                 SIGNAL( activated( QString )),
                 this,
                 SLOT( select( QString )));
        widget->setProperty( "item_id", id );
        if( m_data->m_selectedId.isEmpty() ) {
            select( id );
        }
        emit sigAdded( id, widget );
    }
}


void AbstractContainer::removeWidget( const QString &id )
{
    auto item = m_data->m_items.value( id );
    if( item ) {
        auto theWidget = widget( id );
        m_data->m_selector->removeWidget( item->m_btn );
        m_data->m_stackWidget->removeWidget( item->m_widget );
        m_data->m_items.remove( id );
        if( m_data->m_selectedId == id ) {
            m_data->m_selectedId = m_data->m_items.isEmpty()
                    ? ""
                    : m_data->m_items.begin().key();
            emit sigSelected( m_data->m_selectedId,
                              selectedWidget() );
        }
        updateIndeces();
        theWidget->setProperty( "item_id", QVariant() );
        emit sigRemoved( id );
    }
}


void AbstractContainer::removeWidget( QWidget *widget )
{
    for( auto it = m_data->m_items.begin();
         it != m_data->m_items.end();
         ++ it ) {
        auto item = it.value();
        if( item->m_widget == widget ) {
            removeWidget( it.key() );
            /* I am not breaking here because same widget might have been added
             * multiple times. If later if we find it not important we can break
             * here.
             */
        }
    }
}


void AbstractContainer::select( const QString &id )
{
    auto item = m_data->m_items.value( id );
    if( item ) {
        if( m_data->m_selectedId != ""
                && item->m_index == m_data->m_stackWidget->currentIndex() ) {
            m_data->m_stackWidget->setVisible( false );
            item->m_btn->setChecked( false );
            m_data->m_selectedId = "";
        }
        else {
            auto prev = m_data->m_items.value( m_data->m_selectedId );
            item->m_btn->setChecked( true );
            m_data->m_stackWidget->setCurrentIndex( item->m_index );
            m_data->m_selectedId = id;
            if( prev != nullptr ) {
                prev->m_btn->setChecked( false );
            }
            else {
                m_data->m_stackWidget->setVisible( true );
            }
        }
    }
}

QStackedWidget *AbstractContainer::stackedWidget() const
{
    return m_data->m_stackWidget;
}

QzScroller *AbstractContainer::selector() const
{
    return m_data->m_selector;
}

AbstractContainer::SelectorPosition AbstractContainer::selectorPosition() const
{
    return m_data->m_selectorPosition;
}

Qt::Orientation AbstractContainer::containerOrientation() const
{
    return m_data->m_orientation;
}

Qt::Orientation AbstractContainer::buttonOrientation() const
{
    return  m_data->m_btnOrientation;
}

int AbstractContainer::buttonWidth() const
{
    return m_data->m_btnWidth;
}

int AbstractContainer::buttonHeight() const
{
    return m_data->m_btnHeight;
}


void AbstractContainer::updateIndeces()
{
    for( int i = 0;
         i < m_data->m_stackWidget->count() && i < m_data->m_items.size()
         ; ++ i ) {
        auto widget = m_data->m_stackWidget->widget( i );
        auto itemId = widget->property( "item_id" );
        if( itemId.isValid() ) {
            auto id = itemId.toString();
            auto item = m_data->m_items.value( id );
            item->m_index = i;
        }
    }
}


int AbstractContainer::numWidgets() const
{
    return m_data->m_items.size();
}


bool AbstractContainer::isEmpty()
{
    return m_data->m_items.isEmpty();
}



//Stacked container
StackedContainer::StackedContainer(
        int selectorDimention,
        int buttonDimention,
        AbstractContainer::SelectorPosition selectorPosition,
        Qt::Orientation orientation,
        Qt::Orientation btnOriantation,
        QWidget *parent )
    : AbstractContainer( selectorDimention,
                         buttonDimention,
                         selectorPosition,
                         orientation,
                         btnOriantation,
                         parent )
{
    QBoxLayout *layout = nullptr;
    if( orientation == Qt::Vertical ) {
        layout = new QHBoxLayout();
    } else {
        layout = new QVBoxLayout();
    }
    if( selectorPosition == SelectorPosition::Before ) {
        layout->addWidget( selector() );
        layout->addWidget( stackedWidget() );
        layout->setAlignment(
                    selector(),
                    orientation == Qt::Horizontal ? Qt::AlignTop
                                                  : Qt::AlignLeft );
    }
    else {
        layout->addWidget( stackedWidget() );
        layout->addWidget( selector() );
        layout->setAlignment(
                    selector(),
                    orientation == Qt::Horizontal ? Qt::AlignBottom
                                                  : Qt::AlignRight );
    }
    layout->setContentsMargins( QMargins() );
    this->setLayout( layout );
}

StackedContainer::~StackedContainer()
{

}

QString StackedContainer::containerType() const
{
    return "StackedContainer";
}

}
