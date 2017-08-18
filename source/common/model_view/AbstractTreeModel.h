#pragma once

#include <QAbstractItemModel>

#include "../QuartzCommon.h"

namespace Quartz {

class ITreeNode;

class QUARTZ_COMMON_API AbstractTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    AbstractTreeModel( QObject *parent = nullptr );

    virtual ~AbstractTreeModel();

    QModelIndex index( int row,
                       int column,
                       const QModelIndex &parent ) const override;


    QModelIndex parent( const QModelIndex &child ) const override;

    int rowCount( const QModelIndex &parent ) const override;

    int columnCount( const QModelIndex &parent ) const override;

    QVariant data( const QModelIndex &index, int role ) const override;

    bool hasChildren( const QModelIndex &parent ) const override;

    bool setData( const QModelIndex &index,
                  const QVariant &value,
                  int role ) override;

    Qt::ItemFlags flags( const QModelIndex &index ) const override;


protected:
    virtual ITreeNode * rootAt( int rowIndex ) const = 0;

    virtual int rootCount() const = 0;


};

}
