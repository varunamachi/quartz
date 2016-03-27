#pragma once

#include <QWidget>

class QBoxLayout;
class QScrollArea;
class QPushButton;
class QResizeEvent;

namespace Vam { namespace Quartz {

class QzScroller : public QWidget
{
    Q_OBJECT
public:
    explicit QzScroller( Qt::Orientation orientation,
                         int minimumDim,
                         int maximumDim,
                         QWidget *parent = nullptr );

    QWidgetList widgets() const;

public slots:
    void addWidget( QWidget *widget );

    void removeWidget( QWidget *widget );

protected:
    void resizeEvent( QResizeEvent *event ) override;

private slots:
    void start();

    void stop();

    void onTimeout();

    void adjustArrows();

private:
    Qt::Orientation m_orientation;

    QBoxLayout *m_layout;

    QScrollArea *m_scroll;

    QPushButton *m_bckButton;

    QPushButton *m_fwdButton;

    QTimer *m_timer;

    int m_timeout;

};

} }
