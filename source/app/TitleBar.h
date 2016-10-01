#pragma once

#include <QWidget>

class QPushButton;

namespace Quartz {

class QuartzItem;
class QzScroller;

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar( int height, QWidget *parent = nullptr );

    void addItem( QuartzItem *item );

    void removeItem( QuartzItem *item );

    void removeItem( const QString &item );

    QList< QuartzItem * > items() const;

    QList< QuartzItem * > items(const QString category);

    void removeCategory( const QString &category );

signals:
    void sigMinimizeRequested();

    void sigMaxRestoreRequested();

    void sigCloseRequested();

protected:
    void mouseDoubleClickEvent( QMouseEvent *event );

private:
    int m_height;

    QHash< QString, QuartzItem *> m_items;

    QzScroller *m_scroller;

    QPushButton *m_closeBtn;

    QPushButton *m_maxRestoreBtn;

    QPushButton *m_minimizeBtn;

};

}
