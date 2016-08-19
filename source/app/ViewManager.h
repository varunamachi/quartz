#pragma once

#include <QWidget>
#include <QWidget>
#include <QHash>
#include <QStackedWidget>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QVBoxLayout>

#include <common/widgets/QzScroller.h>
#include <common/widgets/StackedContainer.h>

#include "interface/IQuartzViewManager.h"


namespace Quartz {


class ViewManager : public QWidget
                  , public IQuartzViewManager
{
    Q_OBJECT
public:
    explicit ViewManager( int height,
                          int btnWidth,
                          QWidget *parent = 0 );

    void addView( QuartzView *view ) override;

    void removeView( const QString &viewId ) override;

    void removeView( QuartzView *view ) override;

    void removeViewCategory( const QString &categoryId ) override;

    QuartzView * view( const QString &viewId ) const override;

    QList< QuartzView *> views() const override;

    QList< QuartzView *> views( const QString &categoryId ) const override;

    QuartzView * currentView() const override;

    const QString currentCategory() const override;

    QList< QString > categories() const override;

    void selectView( QString viewId ) override;

private:
    int m_height;

    int m_btnWidth;

    StackedContainer *m_viewContainer;

    QHash< QString, QuartzView *> m_views;

    QMultiHash< QString, QuartzView *> m_categoriesToViews;
};

}
