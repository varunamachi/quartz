#pragma once

#include <QTreeView>

#include "../QuartzCommon.h"

namespace Quartz {

class QUARTZ_COMMON_API QzTreeView : public QTreeView
{
    Q_OBJECT

public:
    QzTreeView( QWidget *parent = nullptr );

    ~QzTreeView();

    void mousePressEvent( QMouseEvent *event ) override;

private:

};

}
