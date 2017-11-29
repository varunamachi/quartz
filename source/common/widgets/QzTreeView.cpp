
#include <QMouseEvent>
#include <QHeaderView>
#include <QAction>
#include <QMenu>

#include <core/logger/Logging.h>

#include "../model_view/TreeNode.h"
#include "QzTreeView.h"

namespace Quartz {

struct QzTreeView::Data
{
    explicit Data( QzTreeView *parent )
        : m_contextMenu{ new QMenu{ parent }}
    {

    }

//    QHash< QString, ContextMenuItem > m_items;

    QHash< QString, QAction *> m_actions;

    QMenu *m_contextMenu;
};

QzTreeView::QzTreeView( QWidget *parent )
    : QTreeView{ parent }
    , m_data{ new Data{ this }}
{
    this->header()->setSectionResizeMode( QHeaderView::ResizeToContents );
    this->setAlternatingRowColors( true );
    this->setStyleSheet( "QTreeView::item{ height: 20px; }");
    this->setContextMenuPolicy( Qt::CustomContextMenu );
    //(const QPoint &)
    connect(this,
            &QTreeView::customContextMenuRequested,
            [ this ]( const QPoint &point ){
        QModelIndex index = this->indexAt(point);
        if( index.isValid() ) {
            m_data->m_contextMenu->exec(
                        this->viewport()->mapToGlobal( point ));
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
//        if( node != nullptrl
//                && node->isEditable( index.column() )
//                && node-> != QVariant::) {
//            edit( index );
//        }
//    }
    QTreeView::mousePressEvent( event );
}

void QzTreeView::addContextAction( ContextMenuItem cm )
{

    auto action = new QAction{ cm.m_name, this };
    connect( action, &QAction::triggered, [ cm, this ](){
        auto modelIdx = currentIndex();
        if( modelIdx.isValid() ) {
            cm.m_func( modelIdx );
        }
    });
    m_data->m_contextMenu->addAction( action );
    m_data->m_actions.insert( cm.m_name, action );
}

void QzTreeView::removeContextMenu( const QString &name )
{
    auto action = m_data->m_actions.value( name );
    if( action != nullptr ) {
        m_data->m_contextMenu->removeAction( action );
    }
}

}
