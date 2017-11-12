
#include <QMouseEvent>

#include "../model_view/TreeNode.h"
#include "QzTreeView.h"

namespace Quartz {

QzTreeView::QzTreeView( QWidget *parent )
    : QTreeView{ parent }
{

}

QzTreeView::~QzTreeView()
{

}

void QzTreeView::mousePressEvent( QMouseEvent *event )
{
    QTreeView::mousePressEvent( event );
    if( event->button() == Qt::LeftButton ) {
        QModelIndex index = indexAt( event->pos() );
        auto node = static_cast< TreeNode *>( index.internalPointer() );
        if( node != nullptr && node->isEditable( index.column() )) {
            edit( index );
        }
    }
}

}
