

#include "TreeNode.h"
#include "AbstractTreeModel.h"


namespace Quartz {

struct AbstractTreeModel::Data
{
    Data( bool selectable, int numFields )
        : m_selectable{ selectable }
        , m_fields{ numFields }
    {
        if( m_selectable ) {
            ++ m_fields;
        }
    }

    bool m_selectable;

    int m_fields;
};

AbstractTreeModel::AbstractTreeModel(
        bool selectable,
        int numFields,
        QObject *parent )
    : QAbstractItemModel{ parent }
    , m_data{ new Data{ selectable, numFields }}
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

int AbstractTreeModel::columnCount( const QModelIndex& parent ) const
{
    //default is list of templates
//    auto count = 0;
//    if( parent.isValid() ) {
//        auto node = static_cast< TreeNode *>( parent.internalPointer() );
//        count = node->numFields();
//    } else if( rootCount() != 0 ){
//        count = rootAt( 0 )->numFields();
//    }
//    return count;
    return m_data->m_fields;
}

QVariant AbstractTreeModel::data( const QModelIndex& index,
                                  int role ) const
{
    if( index.isValid() ) {
        auto node = static_cast< TreeNode *>( index.internalPointer() );
        if( node != nullptr ) {
            if( role == Qt::CheckStateRole
                    && m_data->m_selectable
                    && index.column() == 0 ) {
                return node->isSelected() ? Qt::Checked : Qt::Unchecked;
            }
            else {
                auto data = node->data( index.column() );
                if ( role == Qt::CheckStateRole && data.canConvert< bool >() ) {
                    return data.toBool() ? Qt::Checked : Qt::Unchecked;
                }
                if( role == Qt::DisplayRole || role == Qt::EditRole ) {
                    return data;
                }
                if( role == Qt::ToolTipRole ) {
                    return "Tool tip";
                }
            }
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
            if ( role == Qt::CheckStateRole && value.canConvert< bool >() ) {
                auto val = value.toInt();
                node->setSelected( val == Qt::Checked );
            }
            if( role == Qt::EditRole && ! value.canConvert< bool >()) {
                node->setData( index.column(), value );
            }
        }
    }
    return set;
}

Qt::ItemFlags AbstractTreeModel::flags( const QModelIndex &index ) const
{
    if( ! index.isValid() ) {
        return 0;
    }
    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
//    auto node = static_cast< TreeNode *>( index.internalPointer() );
//    if( node != nullptr ) {
//        if( data( index ) )

//        if( node->isSelectable() && index.column() == 0 ) {
//            flags |= Qt::ItemIsUserCheckable;
//        }
//        else {
//            flags |= Qt::ItemIsEditable;
//        }
//    }
    return flags;
}


}
