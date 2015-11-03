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


namespace Vam { namespace Quartz {

namespace {

class IdButton : public QPushButton
{
    Q_OBJECT
public:
    IndexButton( QString id,
                 QString text,
                 QWidget *parent = 0 )
        : QPushButton( parent )
        , m_id( index )
    {
        setCheckable( true );
        setStyleSheet(
                    " QPushButton {"
                    "     border-radius: 5px;"
                    "     background-color: regba( 32, 32, 32, 200 );"
                    "     min-width: 60px;"
                    "     min-height: 60px;"
                    "     font-size: 10px;"
                    " }"
                    " QPushButton:checked {"
                    "     background-color: #FFA858;"
                    "     color: #202020;"
                    " }"
         );
        setText( text );
    }

protected:
    void mousePressEvent( QMouseEvent *evt )
    {
        if( ! isChecked() ) {
            QPushButton::mousePressEvent( evt );
            emit activated( m_id );
        }
        evt->ignore();
    }

signals:
    void activated( QString id );

private:
    int m_id;
};

class PageContainer : public QWidget
{
    Q_OBJECT
public:

private:
};

}


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

    const QString & currentCategory() const;

    QStringList categories() const;

    void selectCategory( QString categoryId );

    void selectPage( QString pageId );

private:
    int m_holderHeight;

    int m_selectorWidth;

    QzScroller *m_catSelector;

    QHash< QString, QzScroller *> m_pageHolders;

    QHash< QString, QuartzPage *> m_pages;

    QStackedWidget *m_mainWidget;

};

} }
