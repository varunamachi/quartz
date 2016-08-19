#pragma once

#include <QWidget>
#include <QHBoxLayout>

#include <common/widgets/QzScroller.h>

#include "interface/IQuartzActionBar.h"


namespace Quartz {

class ActionBar : public QWidget
                , public IQuartzActionBar
{
    Q_OBJECT
public:
    explicit ActionBar( int height, QWidget *parent = nullptr );

    void addItem( QuartzItem *item );

    void removeItem( QuartzItem *item );

    void removeItem( const QString &item );

    QList< QuartzItem * > items() const;

    QList< QuartzItem * > items(const QString category);

    void removeCategory( const QString &category );

private:
    int m_height;

    QzScroller *m_scroller;

    QHash< QString, QuartzItem *> m_items;
};


}
