#pragma once

#include <quartz_core/IQuartzTitleBar.h>
#include <quartz_common/widgets/QzScroller.h>

namespace Vam { namespace Quartz {

class TitleBar : public QWidget
               , public IQuartzTitleBar
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

private:
    int m_height;

    QHash< QString, QuartzItem *> m_items;

    QzScroller *m_scroller;

    QPushButton *m_closeBtn;

    QPushButton *m_maxRestoreBtn;

    QPushButton *m_minimizeBtn;

};

} }
