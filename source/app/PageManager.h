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


namespace Vam { namespace Quartz {

//class QuartzComponent : public QWidget
//{
//    Q_OBJECT

//public:
//    QuartzComponent( QWidget *parent = 0 )
//        : QWidget( parent )
//    {

//    }

//    virtual QString componentId() const = 0;

//    virtual QString componentName() const = 0;

//    virtual const QIcon* icon() const = 0;
//};


class IndexButton : public QPushButton
{
    Q_OBJECT
public:
    IndexButton( int index, QString text, QWidget *parent = 0 ) :
        QPushButton( parent ),
        m_index( index )
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
            emit activated( m_index );
        }
        evt->ignore();
    }

signals:
    void activated( int index );

private:
    int m_index;
};


class PageManager : public QWidget
                  , public IQuartzPageManager
{
    Q_OBJECT
public:
    explicit PageManager( QWidget *parent = 0 );

    virtual ~PageManager();

    QList< QuartzPage *> pages() const;

    QuartzPage * page( QString pageId ) const;

    QuartzPage * currentPage() const;

    static void destroy();

    static PageManager* get();

signals:
    void componentSelected( const QuartzComponent *component );

    void componentAdded( const QuartzComponent *component );

    void exitRequested();

    void minimizeReqested();


public slots:
    void addComponent( QuartzComponent *component );

    void selectComponent( QString componentId );

private slots:
    void onIndexSelected( int row );

private:

    void setupUi();

    static PageManager *s_instance;

    QHash< QString, QuartzComponent *> m_components;

    QList< IndexButton *> m_buttons;

    QHash< QString, int > m_nameToIndex;

    QStackedWidget *m_mainWidget;

    QVBoxLayout *m_buttonLayout;
};

} }
