#pragma once

#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSizeGrip>

#include "PageManager.h"
#include "ViewManager.h"
#include "ActionBar.h"
#include "TitleBar.h"

namespace Vam { namespace Quartz {

class PageManager;
class ActionBar;

class QzMainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QzMainWidget( QMainWindow *parent = 0 );

    TitleBar * titleBar();

public slots:
    void onAboutToQuit();

    void setRoundedRect( bool useRoundedRect )
    {
        m_roundedRect = useRoundedRect;
    }

protected:
    void paintEvent( QPaintEvent *event );

private:
    QString createStyleSheet();

    bool m_roundedRect;

    TitleBar *m_titleBar;

    PageManager *m_pageManager;

    ViewManager *m_viewManager;

    ActionBar *m_actionBar;

    friend class ChilliWindow;

};


class QuartzWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuartzWindow( QWidget *parent = 0 );

    void mouseMove( QPoint newPos, QPoint oldPos );

private slots:
    void onMaximizeRestore();

    void onMinimize();

protected:
    void mouseMoveEvent( QMouseEvent* event );

    void mousePressEvent( QMouseEvent* event );

    void mouseReleaseEvent( QMouseEvent* event );

    void showEvent( QShowEvent *evt );

    void resizeEvent( QResizeEvent *evt );

private:
    void maximize();

    void restore();

    void minimize();

//    ChilliMainWidget *m_chilliWidget;
    QzMainWidget *m_chilliWidget;

    bool m_moving;

    bool m_maximised;

    QPoint m_lastMousePosition;

    QByteArray m_geometry;

    QHBoxLayout *m_layout;

    QWidget *m_containerWidget;

    bool m_cursorAtLeft;

    bool m_cursorAtRight;

    bool m_cursorAtBottom;

    bool m_resizing;

};

} }
