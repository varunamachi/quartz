#pragma once

#include <QWidget>

class QBoxLayout;
class QScrollArea;
class QPushButton;

namespace Vam { namespace Quartz {

class QzScroller : public QWidget
{
    Q_OBJECT
public:
    explicit QzScroller( Qt::Orientation orientation,
                         int minimumDim,
                         int maximumDim,
                         QWidget *parent = nullptr );

    QWidgetList widget() const;

public slots:
    void addWidget( QWidget *widget );

    void removeWidget( QWidget *widget );

private slots:
    void start();

    void stop();

    void onTimeout();

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
