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

#include <core/extension_system/IPluginAdapter.h>

#include "../QuartzBase.h"

namespace Quartz {

class QuartzView;
class AbstractContainer;
class QzScroller;

class QUARTZ_BASE_API ViewManager : public QWidget
                                  , public IPluginAdapter
{
    Q_OBJECT
public:
    explicit ViewManager( AbstractContainer *container,
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

public:
    const QString & pluginType() const;

    const QString & pluginAdapterName() const;

    bool handlePlugin( AbstractPlugin *plugin );

    bool finalizePlugins();

    static const QString ADAPTER_NAME;

private:
    int m_height;

    int m_btnWidth;

    AbstractContainer *m_viewContainer;

    QHash< QString, QuartzView *> m_views;

    QMultiHash< QString, QuartzView *> m_categoriesToViews;

    QVector< QuartzView *> m_pluginViews;

};

}
