

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
    QModelIndex index;
    if( ! hasIndex( row, column, parent )) {
        return index;
    }
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
        auto node = static_cast< ITreeNode *>( index.internalPointer() );
        if( node != nullptr ) {
            if ( role == Qt::CheckStateRole
                      && node->isSelectable()
                      && index.column() == 0 ) {
                data = node->isSelected() ? Qt::Checked : Qt::Unchecked;
            }
            if( role == Qt::DisplayRole
                      && ! (index.column() == 0 && node->isSelectable() )) {
                data = node->data( index.column() );
            }
            if( role == Qt::EditRole
                    && ! (index.column() == 0 && node->isSelectable() )) {
                data = node->data( index.column() );
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
        auto node = static_cast< ITreeNode *>( index.internalPointer() );
        if( node != nullptr ) {
            if ( role == Qt::CheckStateRole
                      && node->isSelectable()
                      && index.column() == 0 ) {
                auto val = value.toInt();
                node->setSelected( val == Qt::Checked );
            }
            if( role == Qt::EditRole
                      && ! (index.column() == 0 && node->isSelectable() )) {
                node->setData( index.column(), value );
            }
        }

    }
    emit dataChanged(index, index);
    return set;
}

Qt::ItemFlags AbstractTreeModel::flags( const QModelIndex &index ) const
{
    if( ! index.isValid() ) {
        return 0;
    }
    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    auto node = static_cast< ITreeNode *>( index.internalPointer() );
    if( node != nullptr && node->isEditable( index.column() )) {
        if( node->isSelectable() && index.column() == 0 ) {
            flags |= Qt::ItemIsUserCheckable;
        }
        else {
            flags |= Qt::ItemIsEditable;
        }
    }
    return flags;
}


}
