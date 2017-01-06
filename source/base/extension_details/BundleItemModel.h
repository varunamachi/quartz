#pragma once

#include <memory>

#include <QAbstractItemModel>

namespace Quartz {

class AbstractPluginBundle;

class BundleItemModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum class NumCols
    {
        ONE,
        TWO,
        THREE
    };

    explicit BundleItemModel( QObject *parent = nullptr );

    ~BundleItemModel();

    QModelIndex index( int row,
                       int column,
                       const QModelIndex &parent ) const override;

    QModelIndex parent( const QModelIndex &child ) const override;

    int rowCount( const QModelIndex &parent ) const override;

    int columnCount( const QModelIndex &parent ) const override;

    QVariant data( const QModelIndex &index, int role ) const override;

    bool hasChildren( const QModelIndex &parent ) const override;

    void setBundleList( const QVector< AbstractPluginBundle *> *bundles );

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};


}
