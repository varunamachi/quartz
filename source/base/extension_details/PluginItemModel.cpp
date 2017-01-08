
#include <core/extension_system/AbstractPluginBundle.h>
#include <core/extension_system/AbstractPlugin.h>

#include "PluginItemModel.h"

namespace Quartz {

const int NUM_COLS = 3;

struct PluginItemModel::Data
{
    Data()
        : m_pluginList{ nullptr }
    {

    }

    const PluginList *m_pluginList;

};


PluginItemModel::PluginItemModel( QObject *parent )
    : QAbstractItemModel{ parent }
    , m_data{ new Data{ }}
{

}

PluginItemModel::~PluginItemModel()
{

}

QModelIndex PluginItemModel::index( int row,
                                    int column,
                                    const QModelIndex &parent ) const
{
    auto index = QModelIndex();
    if( hasIndex( row, column, parent )) {
        const auto &bundle = m_data->m_pluginList->at( row );
        if( bundle != nullptr ) {
            index = createIndex( row, column, bundle.get() );
        }
    }
    return index;
}

QModelIndex PluginItemModel::parent( const QModelIndex &/*child*/ ) const
{
    return QModelIndex{ };
}

int PluginItemModel::rowCount( const QModelIndex &/*parent*/ ) const
{
    auto size = m_data->m_pluginList != nullptr ? m_data->m_pluginList->size()
                                                : 0;
    return size;
}

int PluginItemModel::columnCount( const QModelIndex &/*parent*/ ) const
{
    return NUM_COLS;
}

QVariant PluginItemModel::data( const QModelIndex &index, int role ) const
{
    if( ! index.isValid()
            || m_data->m_pluginList == nullptr
            || index.row() >= m_data->m_pluginList->size() ) {
        return QVariant();
    }
    if ( role == Qt::TextAlignmentRole ) {
        return int ( Qt::AlignLeft | Qt::AlignVCenter );
    }
    else if ( role == Qt::DisplayRole ) {
        const auto &plugin = m_data->m_pluginList->at( index.row() );
        switch( index.column() ) {
        case 0: return plugin->pluginType();
        case 1: return plugin->pluginId();
        case 2: return plugin->pluginName();
        }
    }
    return QVariant();
}

bool PluginItemModel::hasChildren( const QModelIndex &parent ) const
{
    if( parent.isValid() ) {
        return false;
    }
    return true;
}

QVariant PluginItemModel::headerData(
        int section,
        Qt::Orientation /*orientation*/,
        int role ) const
{
    if ( role == Qt::TextAlignmentRole ) {
        return int( Qt::AlignLeft | Qt::AlignVCenter );
    }
    else if ( role == Qt::DisplayRole ) {
        switch( section ) {
        case 0: return tr( "Type" );
        case 1: return tr( "Id" );
        case 2: return tr( "Name" );
        }
    }
    return QVariant();
}

void PluginItemModel::clear()
{
    beginResetModel();
    m_data->m_pluginList = nullptr;
    endResetModel();
}

void PluginItemModel::setPluginList( const PluginList *plugins )
{
    beginResetModel();
    m_data->m_pluginList = plugins;
    endResetModel();
}




}
