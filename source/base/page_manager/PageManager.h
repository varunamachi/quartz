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

class QuartzPage;
class QzScroller;
class StackedContainer;


class QUARTZ_BASE_API PageManager : public QWidget
                                  , public IPluginAdapter
{
    Q_OBJECT
public:
    explicit PageManager( int categoryWidth,
                          int pagerHeight,
                          QWidget *parent = 0 );

    void addPage( QuartzPage *page );

    void removePage( const QString &pageId );

    void removePage( QuartzPage *page );

    void removePageCategory( const QString &categoryId );

    QuartzPage * page( const QString &pageId ) const;

    QList< QuartzPage *> pages() const ;

    QList< QuartzPage *> pages( const QString &categoryId ) const;

    QuartzPage * currentPage() const;

    const QString currentCategory() const;

    QStringList categories() const;

    void selectCategory( QString categoryId );

    void selectPage( QString pageId );

    // IPluginAdapter interface
public:
    const QString &pluginType() const;

    const QString &pluginAdapterName() const;

    bool handlePlugin(IPlugin *plugin);

    bool finalizePlugins();

    static const QString ADAPTER_NAME;

private:
    int m_selectorWidth;

    int m_holderHeight;

    StackedContainer *m_catContainer;

    QHash< QString, StackedContainer *> m_pageContainers;

    QHash< QString, QuartzPage *> m_pages;

    QVector< QuartzPage *> m_pluginPages;



};

}
