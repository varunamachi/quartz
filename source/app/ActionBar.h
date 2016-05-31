#pragma once

#include <QWidget>
#include <QHBoxLayout>

#include <quartz_core/IQuartzActionBar.h>
#include <quartz_common/widgets/QzScroller.h>


namespace Vq { namespace Quartz {

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


} }
