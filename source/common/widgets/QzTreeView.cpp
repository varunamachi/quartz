
#include <QMouseEvent>
#include <QHeaderView>

#include "../model_view/TreeNode.h"
#include "QzTreeView.h"

namespace Quartz {

QzTreeView::QzTreeView( QWidget *parent )
    : QTreeView{ parent }
{
    this->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->setAlternatingRowColors( true );
    this->setStyleSheet( "QTreeView::item{height: 20px;}");
}

QzTreeView::~QzTreeView()
{

}

void QzTreeView::mousePressEvent( QMouseEvent *event )
{
//    if( event->button() == Qt::LeftButton ) {
//        QModelIndex index = indexAt( event->pos() );
//        auto node = static_cast< TreeNode *>( index.internalPointer() );
//        if( node != nullptr
//                && node->isEditable( index.column() )
//                && node-> != QVariant::) {
//            edit( index );
//        }
//    }
    QTreeView::mousePressEvent( event );
}

}
