
#include "BundleListModel.h"

namespace Quartz {

struct BundleListModel::Data
{

};

BundleListModel::BundleListModel( QObject *parent )
    : QAbstractItemModel{ parent }
    , m_data{ new Data }
{

}

BundleListModel::~BundleListModel()
{

}

QModelIndex BundleListModel::index( int row,
                                    int column,
                                    const QModelIndex &parent ) const
{
    return QModelIndex{ };
}

QModelIndex BundleListModel::parent( const QModelIndex &child ) const
{
    return QModelIndex{ };
}

int BundleListModel::rowCount( const QModelIndex &parent ) const
{
    return 0;
}

int BundleListModel::columnCount( const QModelIndex &parent ) const
{
    return 0;
}

QVariant BundleListModel::data( const QModelIndex &index, int role ) const
{
    return QVariant{ };
}




}
