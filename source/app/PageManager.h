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

#include <quartz_core/IQuartzPageManager.h>
#include <quartz_common/widgets/QzScroller.h>
#include <quartz_common/widgets/StackedContainer.h>


namespace Vam { namespace Quartz {


class PageManager : public QWidget
                  , public IQuartzPageManager
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

    QList< QuartzPage *> pages();

    QList< QuartzPage *> pages( const QString &categoryId ) const;

    QuartzPage * currentPage() const;

    const QString currentCategory() const;

    QStringList categories() const;

    void selectCategory( QString categoryId );

    void selectPage( QString pageId );

private:
    StackedContainer *m_catContainer;

    QHash< QString, StackedContainer *> m_pageContainers;

    QHash< QString, QuartzPage *> m_pages;


};

} }
