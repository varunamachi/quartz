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

#include <quartz_core/IQuartzViewManager.h>
#include <quartz_common/widgets/QzScroller.h>
#include <quartz_common/widgets/StackedContainer.h>


namespace Vam { namespace Quartz {


class ViewManager : public QWidget
                  , public IQuartzViewManager
{
    Q_OBJECT
public:
    explicit ViewManager( int categoryWidth,
                          int viewrHeight,
                          QWidget *parent = 0 );

    void addView( QuartzView *view ) override;

    void removeView( const QString &viewId ) override;

    void removeView( QuartzView *view ) override;

    void removeViewCategory( const QString &categoryId ) override;

    QuartzView * view( const QString &viewId ) const override;

    QList< QuartzView *> views() const override;

    QList< QuartzView *> views( const QString &categoryId ) const override;

    QuartzView * currentView() const override;

    const QString & currentCategory() const override;

    QStringList categories() const override;

    void selectCategory( QString categoryId ) override;

    void selectView( QString viewId ) override;

private:
    int m_selectorWidth;

    int m_holderHeight;

    StackedContainer *m_catContainer;

    QHash< QString, StackedContainer *> m_viewContainers;

    QHash< QString, QuartzView *> m_views;


};

} }
