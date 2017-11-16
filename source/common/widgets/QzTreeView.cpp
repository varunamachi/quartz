
#include <QMouseEvent>
#include <QHeaderView>
#include <QAction>
#include <QMenu>

#include "../model_view/TreeNode.h"
#include "QzTreeView.h"

namespace Quartz {

struct QzTreeView::Data
{
    explicit Data( QzTreeView *parent )
        : m_contextMenu{ new QMenu{ parent }}
    {

    }

    QMenu *m_contextMenu;
};

QzTreeView::QzTreeView( QWidget *parent )
    : QTreeView{ parent }
    , m_data{ new Data{ this }}
{
    this->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->setAlternatingRowColors( true );
    this->setStyleSheet( "QTreeView::item{height: 20px;}");
    this->setContextMenuPolicy( Qt::CustomContextMenu );
    //(const QPoint &)
    connect(this,
            &QTreeView::customContextMenuRequested,
            [ this ]( const QPoint &point ){
        QModelIndex index = this->indexAt(point);
        if (index.isValid() && index.row() % 2 == 0) {
            m_data->m_contextMenu->exec( this->viewport()->mapToGlobal(point) );
        }
    });
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

void QzTreeView::addContextAction( QAction *action )
{
    m_data->m_contextMenu->addAction( action );
}

}
