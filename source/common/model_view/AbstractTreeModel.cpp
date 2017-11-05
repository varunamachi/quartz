

#include "ITreeNode.h"
#include "AbstractTreeModel.h"


namespace Quartz {

AbstractTreeModel::AbstractTreeModel( QObject *parent )
    : QAbstractItemModel{ parent }
{

}


AbstractTreeModel::~AbstractTreeModel()
{

}


QModelIndex AbstractTreeModel::index( int row,
                                      int column,
                                      const QModelIndex &parent ) const
{
//    if( ! hasIndex( row, column, parent )) {
//        return index;
//    }
    QModelIndex index;
    if( parent.isValid() ) {
        auto node = static_cast< ITreeNode * >( parent.internalPointer() );
        auto child = node->child( row );
        if( child != nullptr ) {
            index = createIndex( row, column, child );
        }
    } else {
        auto node = rootAt( row );
        if( node != nullptr ) {
            index = createIndex( row, column, node );
        }
    }
    return index;
}


QModelIndex AbstractTreeModel::parent( const QModelIndex& childIndex ) const
{
    if( ! childIndex.isValid() ) {
        return QModelIndex{};
    }
    auto index = QModelIndex{};
    auto node = static_cast< ITreeNode *>( childIndex.internalPointer() );
    if( node != nullptr && node->parent() != nullptr ) {
        auto parent = node->parent();
        auto grandParent = parent->parent();
        auto row = 0;
        if( grandParent != nullptr ) {
            row = grandParent->indexOfChild( parent );
        }
        if( row != -1 ) {
            //only zeroth column ??
            index = createIndex( row, 0, parent );
        }
    }
    return index;

}

int AbstractTreeModel::rowCount( const QModelIndex& parent ) const
{
    //default is list of templates
    auto count = rootCount();
    if( parent.isValid() ) {
        auto node = static_cast< ITreeNode *>( parent.internalPointer() );
        count = node->numChildren();
    }
    return count;
}

int AbstractTreeModel::columnCount( const QModelIndex& parent ) const
{
    //default is list of templates
    auto count = 0;
    if( parent.isValid() ) {
        auto node = static_cast< ITreeNode *>( parent.internalPointer() );
        count = node->numFields();
    } else if( rootCount() != 0 ){
        count = rootAt( 0 )->numFields();
    }
    return count;
}

QVariant AbstractTreeModel::data( const QModelIndex& index,
                                int role ) const
{
    QVariant data;
    if( index.isValid() ) {
        if( role == Qt::DisplayRole ) {
            auto node = static_cast< ITreeNode *>( index.internalPointer() );
            if( node != nullptr ) {
                data = node->data( index.column() )            ;
            }
        }
    }
    return data;
}

bool AbstractTreeModel::hasChildren( const QModelIndex& parent ) const
{
    auto has = rootCount() != 0;
    if(  parent.isValid() ) {
        auto node = static_cast< ITreeNode *>( parent.internalPointer() );
        has = node->numChildren() != 0;
    }
    return has;
}

bool AbstractTreeModel::setData( const QModelIndex &index,
                                 const QVariant &value,
                                 int role )
{
    bool set = false;
    if( index.isValid() ) {
        if( role == Qt::EditRole ) {
            auto node = static_cast< ITreeNode *>( index.internalPointer() );
            if( node != nullptr ) {
                node->setData( index.column(), value );
                set = true;
            }
        }
    }
    return set;
}

Qt::ItemFlags AbstractTreeModel::flags( const QModelIndex &index ) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags( index );
    auto node = static_cast< ITreeNode *>( index.internalPointer() );
    if( node != nullptr && node->isEditable( index.column() )) {
            return flags |= Qt::ItemIsEditable;
    }
    return flags;
}


}
