
#include <core/extension_system/AbstractPluginBundle.h>

#include "BundleItemModel.h"

namespace Quartz {

const int NUM_COLS = 1;

struct BundleItemModel::Data
{
    Data()
        : m_bundleList{ nullptr }
    {

    }

    const QVector< AbstractPluginBundle *> *m_bundleList;

};


BundleItemModel::BundleItemModel( QObject *parent )
    : QAbstractItemModel{ parent }
    , m_data{ new Data{ }}
{

}

BundleItemModel::~BundleItemModel()
{

}

QModelIndex BundleItemModel::index( int row,
                                     int column,
                                     const QModelIndex &/*parent*/ ) const
{
    return createIndex( row, column );
}

QModelIndex BundleItemModel::parent( const QModelIndex &/*child*/ ) const
{
    return QModelIndex{ };
}

int BundleItemModel::rowCount( const QModelIndex &/*parent*/ ) const
{
    auto size = m_data->m_bundleList != nullptr ? m_data->m_bundleList->size()
                                                : 0;
    return size;
}

int BundleItemModel::columnCount( const QModelIndex &/*parent*/ ) const
{
    return NUM_COLS;
}

QVariant BundleItemModel::data( const QModelIndex &index, int role ) const
{
    if( ! index.isValid()
            || m_data->m_bundleList == nullptr
            || index.row() >= m_data->m_bundleList->size() ) {
        return QVariant();
    }
    if ( role == Qt::TextAlignmentRole ) {
        return int ( Qt::AlignLeft | Qt::AlignVCenter );
    }
    else if ( role == Qt::DisplayRole ) {
        const auto &bundle = m_data->m_bundleList->at( index.row() );
        switch( index.column() ) {
        case 0: return bundle->bundleId();
        case 1: return bundle->bundleName();
//        case 2: return library
        }
    }
    return QVariant();
}

bool BundleItemModel::hasChildren( const QModelIndex &/*parent*/ ) const
{
    return false;
}

void BundleItemModel::setBundleList(
        const QVector< AbstractPluginBundle *> *bundle )
{
    m_data->m_bundleList = bundle;
}




}
