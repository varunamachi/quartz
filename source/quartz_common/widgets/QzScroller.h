#pragma once

#include <QWidget>

class QBoxLayout;
class QScrollArea;

namespace Vam { namespace Quartz {

class QzScroller : public QWidget
{
    Q_OBJECT
public:
    explicit QzScroller( Qt::Orientation orientation,
                         QWidget *parent = nullptr );

private slots:
    void whenForward();

    void whenBackward();

private:
    Qt::Orientation m_orientation;

    QBoxLayout *m_layout;

    QScrollArea *m_scroll;

};

} }
