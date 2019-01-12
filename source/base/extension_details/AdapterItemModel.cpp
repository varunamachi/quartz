
#include <core/ext/Plugin.h>
#include <core/ext/IExtensionAdapter.h>

#include "AdapterItemModel.h"

namespace Quartz { namespace Ext {

const int NUM_COLS = 2;

struct AdapterItemModel::Data
{
    Data()
        : m_adapterList(nullptr)
    {

    }

    const AdapterList *m_adapterList;

};


AdapterItemModel::AdapterItemModel(QObject *parent)
    : QAbstractItemModel(parent)
    , m_data(std::make_unique<Data>())
{

}

AdapterItemModel::~AdapterItemModel()
{

}

QModelIndex AdapterItemModel::index(int row,
                                     int column,
                                     const QModelIndex &parent) const
{
    auto index = QModelIndex();
    if (hasIndex(row, column, parent)) {
        const auto &plugin = m_data->m_adapterList->at(row);
        if (plugin != nullptr) {
            index = createIndex(row, column, plugin.get());
        }
    }
    return index;
}

QModelIndex AdapterItemModel::parent(const QModelIndex &/*child*/) const
{
    return QModelIndex();
}

int AdapterItemModel::rowCount(const QModelIndex &/*parent*/) const
{
    auto size = m_data->m_adapterList != nullptr ? m_data->m_adapterList->size()
                                                : 0;
    return size;
}

int AdapterItemModel::columnCount(const QModelIndex &/*parent*/) const
{
    return NUM_COLS;
}

QVariant AdapterItemModel::data(const QModelIndex &index, int role) const
{
    if (! index.isValid()
            || m_data->m_adapterList == nullptr
            || index.row() >= m_data->m_adapterList->size()) {
        return QVariant();
    }
    if (role == Qt::TextAlignmentRole) {
        return int (Qt::AlignLeft | Qt::AlignVCenter);
    }
    else if (role == Qt::DisplayRole) {
        const auto &adapter = m_data->m_adapterList->at(index.row());
        switch(index.column()) {
        case 0: return adapter->extensionType();
        case 1: return adapter->extensionAdapterName();
        }
    }
    return QVariant();
}

bool AdapterItemModel::hasChildren(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return false;
    }
    return true;
}

QVariant AdapterItemModel::headerData(
        int section,
        Qt::Orientation /*orientation*/,
        int role) const
{
    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignLeft | Qt::AlignVCenter);
    }
    else if (role == Qt::DisplayRole) {
        switch(section) {
        case 0: return tr("Type");
        case 1: return tr("Id");
        case 2: return tr("Name");
        }
    }
    return QVariant();
}

void AdapterItemModel::clear()
{
    beginResetModel();
    m_data->m_adapterList = nullptr;
    endResetModel();
}

void AdapterItemModel::setAdapterList(
        const QVector<std::shared_ptr<IExtensionAdapter>> *adapters)
{
    beginResetModel();
    m_data->m_adapterList = adapters;
    endResetModel();
}

} }

