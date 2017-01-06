
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
                                     const QModelIndex &/*parent*/ ) const
{
    return createIndex( row, column );
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
        case 0: return plugin->pluginId();
        case 1: return plugin->pluginName();
        case 2: return plugin->pluginType();
        }
    }
    return QVariant();
}

bool PluginItemModel::hasChildren( const QModelIndex &/*parent*/ ) const
{
    return false;
}

void PluginItemModel::setPluginList( const PluginList *plugins )
{
    m_data->m_pluginList = plugins;
}




}
