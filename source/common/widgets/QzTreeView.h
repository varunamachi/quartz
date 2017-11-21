#pragma once

#include <memory>

#include <QTreeView>

#include "../QuartzCommon.h"

class QAction;

namespace Quartz {

struct ContextMenuItem {
    QString m_name;

    std::function< void() > m_func;

    //Icon
};

class QUARTZ_COMMON_API QzTreeView : public QTreeView
{
    Q_OBJECT

public:
    QzTreeView( QWidget *parent = nullptr );

    ~QzTreeView();

    void mousePressEvent( QMouseEvent *event ) override;

    void addContextAction( ContextMenuItem cm );

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

}
