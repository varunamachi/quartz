#pragma once

#include <QWidget>
#include <QHBoxLayout>

#include <quartz_core/IQuartzActionBar.h>


namespace Vam { namespace Quartz {

class ActionBar : public QWidget
                , public IQuartzActionBar
{
    Q_OBJECT
public:
    explicit ActionBar( int height, QWidget *parent = nullptr );

    void addItem( QuartzItem *widget );

    void removeItem( QuartzItem *widget );

    void removeItem( const QString &itemId );

    void removeCategory( const QString &category );

    QList< QuartzItem * > items() const;

    QList< QuartzItem * > items( const QString category );

private:
    int m_height;

    QHBoxLayout *m_layout;

};


} }
