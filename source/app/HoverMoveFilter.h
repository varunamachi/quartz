#pragma once

#include <QObject>

namespace Quartz {

class HoverMoveFilter : public QObject
{
    Q_OBJECT;
public:
    HoverMoveFilter(QObject *parent = nullptr);

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};


}
