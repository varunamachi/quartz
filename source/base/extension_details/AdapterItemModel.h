#pragma once

#include <memory>

#include <QAbstractItemModel>

#include <core/utils/Macros.h>

#include "../QuartzBase.h"

namespace Quartz {

QZ_INTERFACE IPluginAdapter;

class QUARTZ_BASE_API AdapterItemModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit AdapterItemModel( QObject *parent );

    ~AdapterItemModel();

    QModelIndex index( int row,
                       int column,
                       const QModelIndex &parent ) const override;

    QModelIndex parent( const QModelIndex &child ) const override;

    int rowCount( const QModelIndex &parent ) const override;

    int columnCount( const QModelIndex &parent ) const override;

    QVariant data( const QModelIndex &index, int role ) const override;

    bool hasChildren( const QModelIndex &parent ) const override;

    QVariant headerData( int section,
                         Qt::Orientation orientation,
                         int role ) const override;

    void setAdapterList(
            const QVector< std::shared_ptr< IPluginAdapter >> *plugins );

    void clear();

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

}
