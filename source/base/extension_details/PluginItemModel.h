#pragma once

#include <memory>

#include <QAbstractItemModel>

#include "../QuartzBase.h"

namespace Quartz { namespace Ext {

class Plugin;

class QUARTZ_BASE_API PluginItemModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum class NumCols
    {
        One     = 1,
        Two     = 2,
        Three   = 3
    };

    explicit PluginItemModel( NumCols numCols, QObject *parent = nullptr );

    ~PluginItemModel();

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

    void setPluginList( const QVector< const Plugin *> *plugins );

    void clear();

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};


} }
