#pragma once

#include <QAbstractItemModel>


namespace Quartz {

class ITreeNode;

class AbstractTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    QModelIndex index( int row,
                       int column,
                       const QModelIndex &parent ) const override;

    QModelIndex parent( const QModelIndex &child ) const override;

    int rowCount( const QModelIndex &parent ) const override;

    int columnCount( const QModelIndex &parent ) const override;

    QVariant data( const QModelIndex &index, int role ) const override;

    bool hasChildren( const QModelIndex &parent ) const override;

protected:

    virtual ITreeNode * rootAt( int rowIndex ) const = 0;

    virtual int rootCount() const = 0;


private:

};

}
