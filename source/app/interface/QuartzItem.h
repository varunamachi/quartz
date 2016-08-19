#pragma once

#include <QWidget>

namespace Quartz {

class QuartzItem : public QWidget
{
public:
    QuartzItem( const QString &itemId,
                const QString &category )
        : m_itemId( itemId )
        , m_category( category )
    {

    }

    const QString itemId() const
    {
        return m_itemId;
    }

    const QString itemCategory() const
    {
        return m_category;
    }

private:
    QString m_itemId;

    QString m_category;


};

}
