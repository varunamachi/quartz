#pragma once

#include <memory>

#include <QTreeView>

#include "../QuartzCommon.h"

class QAction;

namespace Quartz {

class QUARTZ_COMMON_API QzTreeView : public QTreeView
{
    Q_OBJECT

public:
    QzTreeView( QWidget *parent = nullptr );

    ~QzTreeView();

    void mousePressEvent( QMouseEvent *event ) override;

    void addContextAction( QAction *action ); //later use QzAction with name...

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

}
