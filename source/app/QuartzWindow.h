#pragma once

#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSizeGrip>

namespace Vam { namespace Quartz {

class PageManager;
class ActionBar;

class ChilliMainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChilliMainWidget( QWidget *parent = 0 );

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

    QPushButton *m_maxRestore;

    QIcon *m_maximizeIcon;

    QIcon *m_restoreIcon;

    QWidget *m_leftWidget;

//    PlaylistWidget *m_playlist;

//    AudioPlayerWidget *m_audioPlayer;

    bool m_roundedRect;

    QSizeGrip *m_sizeGrip;

    friend class ChilliWindow;

};


class QuartzWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuartzWindow( QWidget *parent = 0 );

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
    ChilliMainWidget *m_chilliWidget;

    bool m_moving;

    bool m_maximised;

    QPoint m_lastMousePosition;

    QByteArray m_geometry;

    QHBoxLayout *m_layout;

    QWidget *m_containerWidget;

};

} }
