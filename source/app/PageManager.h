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


namespace Vq { namespace Quartz {


class PageManager : public QWidget
                  , public IQuartzPageManager
{
    Q_OBJECT
public:
    explicit PageManager( int categoryWidth,
                          int pagerHeight,
                          QWidget *parent = 0 );

    void addPage( QuartzPage *page ) override;

    void removePage( const QString &pageId ) override;

    void removePage( QuartzPage *page ) override;

    void removePageCategory( const QString &categoryId ) override;

    QuartzPage * page( const QString &pageId ) const override;

    QList< QuartzPage *> pages() const ;

    QList< QuartzPage *> pages( const QString &categoryId ) const override;

    QuartzPage * currentPage() const override;

    const QString currentCategory() const override;

    QStringList categories() const override;

    void selectCategory( QString categoryId ) override;

    void selectPage( QString pageId ) override;

private:
    int m_selectorWidth;

    int m_holderHeight;

    StackedContainer *m_catContainer;

    QHash< QString, StackedContainer *> m_pageContainers;

    QHash< QString, QuartzPage *> m_pages;


};

} }
