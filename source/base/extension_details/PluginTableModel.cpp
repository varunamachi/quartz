
#include "PluginTableModel.h"

namespace Quartz {

struct PluginTableModel::Data
{

};

PluginTableModel::PluginTableModel( QObject *parent )
    : QAbstractItemModel{ parent }
    , m_data{ new Data }
{

}

PluginTableModel::~PluginTableModel()
{

}

QModelIndex PluginTableModel::index( int row,
                                     int column,
                                     const QModelIndex &parent ) const
{
    return QModelIndex{ };
}

QModelIndex PluginTableModel::parent( const QModelIndex &child ) const
{
    return QModelIndex{ };
}

int PluginTableModel::rowCount( const QModelIndex &parent ) const
{
    return 0;
}

int PluginTableModel::columnCount( const QModelIndex &parent ) const
{
    return 0;
}

QVariant PluginTableModel::data( const QModelIndex &index, int role ) const
{
    return QVariant{ };
}




}
