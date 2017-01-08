
#include <QLibrary>

#include <core/extension_system/PluginManager.h>
#include <core/extension_system/AbstractPluginBundle.h>

#include "../QzAppContext.h"
#include "BundleItemModel.h"

namespace Quartz {


struct BundleItemModel::Data
{
    Data( BundleItemModel::NumCols numCols )
        : m_numCols{ numCols }
        , m_bundleList{ nullptr }
    {

    }

    BundleItemModel::NumCols m_numCols;

    const QVector< const AbstractPluginBundle *> *m_bundleList;
};


BundleItemModel::BundleItemModel( BundleItemModel::NumCols numCols,
                                  QObject *parent )
    : QAbstractItemModel{ parent }
    , m_data{ new Data{ numCols }}
{

}

BundleItemModel::~BundleItemModel()
{

}

QModelIndex BundleItemModel::index( int row,
                                    int column,
                                    const QModelIndex &parent ) const
{
    auto index = QModelIndex();
    if( hasIndex( row, column, parent )) {
        const auto &bundle = m_data->m_bundleList->at( row );
        if( bundle != nullptr ) {
            index = createIndex( row,
                                 column,
                                 reinterpret_cast< void *>(
                                     const_cast< AbstractPluginBundle *>(
                                         bundle )));
        }
    }
    return index;
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
    auto cnt = static_cast< int >( m_data->m_numCols );
    return cnt;
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
        auto lib = appContext()->pluginManager()->libraryForBundle(
                    bundle->bundleId() );
        switch( index.column() ) {
        case 0: return bundle->bundleName();
        case 1: return bundle->bundleId();
        case 2:
            if( lib != nullptr ) {
                return lib->fileName();
            }
            break;
        }
    }
    return QVariant();
}

QVariant BundleItemModel::headerData(
        int section,
        Qt::Orientation /*orientation*/,
        int role ) const
{
    if ( role == Qt::TextAlignmentRole ) {
        return int( Qt::AlignLeft | Qt::AlignVCenter );
    }
    else if ( role == Qt::DisplayRole ) {
        switch( section ) {
        case 0: return tr( "Name" );
        case 1: return tr( "Id" );
        case 2: return tr( "Library" );
        }
    }
    return QVariant();
}

bool BundleItemModel::hasChildren( const QModelIndex &parent ) const
{
    if( parent.isValid() ) {
        return false;
    }
    return  true;
}

void BundleItemModel::setBundleList(
        const QVector< const AbstractPluginBundle *> *bundle )
{
    beginResetModel();
    m_data->m_bundleList = bundle;
    endResetModel();
}

void BundleItemModel::clear()
{
    beginResetModel();
    m_data->m_bundleList = nullptr;
    endResetModel();
}

}
