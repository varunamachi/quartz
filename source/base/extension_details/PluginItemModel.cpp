
#include <QLibrary>

#include <core/ext/PluginManager.h>
#include <core/ext/Plugin.h>

#include <common/iconstore/IconFontStore.h>

#include "../QzAppContext.h"
#include "PluginItemModel.h"

namespace Quartz { namespace Ext {


struct PluginItemModel::Data
{
    Data( PluginItemModel::NumCols numCols )
        : m_numCols{ numCols }
        , m_pluginList{ nullptr }
    {

    }

    PluginItemModel::NumCols m_numCols;

    const QVector< const Plugin *> *m_pluginList;
};


PluginItemModel::PluginItemModel( PluginItemModel::NumCols numCols,
                                  QObject *parent )
    : QAbstractItemModel{ parent }
    , m_data{ new Data{ numCols }}
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
        const auto &plugin = m_data->m_pluginList->at( row );
        if( plugin != nullptr ) {
            index = createIndex( row,
                                 column,
                                 reinterpret_cast< void *>(
                                     const_cast< Ext::Plugin *>(
                                         plugin )));
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
    auto cnt = static_cast< int >( m_data->m_numCols );
    return cnt;
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
    } else if ( role == Qt::DisplayRole ) {
        const auto &plugin = m_data->m_pluginList->at( index.row() );
        auto lib = appContext()->pluginManager()->libraryForPlugin(
                    plugin->pluginId() );
        switch( index.column() ) {
        case 0: return plugin->pluginName();
        case 1: return plugin->pluginId();
        case 2:
            if( lib != nullptr ) {
                return lib->fileName();
            }
            break;
        }
    } else if (role == Qt::DecorationRole) {
        return getIcon(MatIcon::Extension);
    }
    return QVariant();
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
        case 0: return tr( "Name" );
        case 1: return tr( "Id" );
        case 2: return tr( "Library" );
        }
    }
    return QVariant();
}

bool PluginItemModel::hasChildren( const QModelIndex &parent ) const
{
    if( parent.isValid() ) {
        return false;
    }
    return  true;
}

void PluginItemModel::setPluginList(
        const QVector< const Ext::Plugin *> *plugins)
{
    beginResetModel();
    m_data->m_pluginList = plugins;
    endResetModel();
}

void PluginItemModel::clear()
{
    beginResetModel();
    m_data->m_pluginList = nullptr;
    endResetModel();
}

} }
