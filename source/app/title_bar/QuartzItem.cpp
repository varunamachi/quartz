
#include "QuartzItem.h"

namespace Quartz {

struct QuartzItem::Data
{
public:
    Data( const QString &itemId, const QString &category )
        : m_itemId( itemId )
        , m_category( category )
    {

    }

    QString m_itemId;

    QString m_category;

};


QuartzItem::QuartzItem( const QString &itemId,
                        const QString &category,
                        QWidget *parent )
    : QWidget( parent )
//    , m_data( std::make_unique< Data >( itemId, category ))
    , m_data( new Data( itemId, category ))
{

}

QuartzItem::~QuartzItem()
{

}

const QString QuartzItem::itemId() const
{
    return m_data->m_itemId;
}

const QString QuartzItem::itemCategory() const
{
    return m_data->m_category;
}

}
