#pragma once

#include <QTreeView>

namespace Quartz {

class QzTreeView : public QTreeView
{
    Q_OBJECT

public:
    QzTreeView( QWidget *parent = nullptr );

    ~QzTreeView();

    void mousePressEvent( QMouseEvent *event ) override;

private:

};

}
