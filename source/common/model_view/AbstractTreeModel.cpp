

#include "TreeNode.h"
#include "AbstractTreeModel.h"


namespace Quartz {

struct AbstractTreeModel::Data
{
    Data( bool selectable, int numFields )
        : m_fields{ numFields }
        , m_selectable{ selectable }
    {
        if( m_selectable ) {
            ++ m_fields;
        }
    }

    int m_fields;

    bool m_selectable;
};

AbstractTreeModel::AbstractTreeModel(
        int numFields,
        bool selectable,
        QObject *parent )
    : QAbstractItemModel{ parent }
    , m_data{ new Data{ selectable, numFields }}
{

}

bool isBool( const QVariant &var ) {
    return var.type() == QVariant::Bool;
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
        auto node = static_cast< TreeNode * >( parent.internalPointer() );
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
    auto node = static_cast< TreeNode *>( childIndex.internalPointer() );
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
        auto node = static_cast< TreeNode *>( parent.internalPointer() );
        count = node->numChildren();
    }
    return count;
}

int AbstractTreeModel::columnCount( const QModelIndex& /*parent*/ ) const
{
    return m_data->m_fields;
}

QVariant AbstractTreeModel::data( const QModelIndex& index,
                                  int role ) const
{
    auto node = static_cast< TreeNode *>( index.internalPointer() );
    if( index.isValid() && node != nullptr ) {
        if( m_data->m_selectable && index.column() == 0 ){
            switch( role ) {
            case Qt::CheckStateRole:
                return node->isSelected() ? Qt::Checked : Qt::Unchecked;
            case Qt::DisplayRole:
            case Qt::EditRole:
                return "";
            }
            return QVariant{};
        }
        auto col = m_data->m_selectable ? index.column() - 1 : index.column();
        auto data = node->data( col );
        if( isBool( data )) {
            switch( role ) {
            case Qt::CheckStateRole:
                return data.toBool() ? Qt::Checked : Qt::Unchecked;
            case Qt::DisplayRole:
            case Qt::EditRole:
                return "";
            }
            return QVariant{};
        }
        if( role == Qt::DisplayRole || role == Qt::EditRole ) {
            return data;
        }
    }
    return QVariant{};
}

bool AbstractTreeModel::hasChildren( const QModelIndex& parent ) const
{
    auto has = rootCount() != 0;
    if(  parent.isValid() ) {
        auto node = static_cast< TreeNode *>( parent.internalPointer() );
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
        auto node = static_cast< TreeNode *>( index.internalPointer() );
        if( node != nullptr ) {
            if ( role == Qt::CheckStateRole ) {
                auto val = value.toInt();
                node->setSelected( val == Qt::Checked );
            }
            else if( role == Qt::EditRole ) {
                node->setData( index.column(), value );
            }
            set = true;
        }
    }
    return set;
}

Qt::ItemFlags AbstractTreeModel::flags( const QModelIndex &index ) const
{
    auto node = static_cast< TreeNode *>( index.internalPointer() );
    if( ! index.isValid() || node == nullptr ) {
        return 0;
    }
    auto col = m_data->m_selectable ? index.column() - 1 : index.column();
    if( m_data->m_selectable && index.column() == 0 ) {
        return Qt::ItemIsEnabled
                | Qt::ItemIsSelectable
                | Qt::ItemIsUserCheckable;
    }
    if( isBool( node->data( col ))) {
        auto flags = Qt::ItemIsEnabled
                | Qt::ItemIsSelectable;
        if( node->isEditable( col )) {
            flags |= Qt::ItemIsUserCheckable | Qt::ItemIsEditable;
        }
    }
    if( node->isEditable( col )) {
        return Qt::ItemIsEnabled
                | Qt::ItemIsSelectable
                | Qt::ItemIsEditable;
    }
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}


}
