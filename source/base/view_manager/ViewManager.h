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

#include "../QuartzBase.h"

namespace Quartz {

class QuartzView;
class StackedContainer;
class QzScroller;

class QUARTZ_BASE_API ViewManager : public QWidget
{
    Q_OBJECT
public:
    explicit ViewManager( int height,
                          int btnWidth,
                          QWidget *parent = 0 );

    void addView( QuartzView *view );

    void removeView( const QString &viewId );

    void removeView( QuartzView *view );

    void removeViewCategory( const QString &categoryId );

    QuartzView * view( const QString &viewId ) const;

    QList< QuartzView *> views() const;

    QList< QuartzView *> views( const QString &categoryId ) const;

    QuartzView * currentView() const;

    const QString currentCategory() const;

    QList< QString > categories() const;

    void selectView( QString viewId );

private:
    int m_height;

    int m_btnWidth;

    StackedContainer *m_viewContainer;

    QHash< QString, QuartzView *> m_views;

    QMultiHash< QString, QuartzView *> m_categoriesToViews;
};

}
