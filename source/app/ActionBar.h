#pragma once

#include <QWidget>
#include <QHBoxLayout>


namespace Quartz {

class QzScroller;
class QuartzItem;

class ActionBar : public QWidget
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
