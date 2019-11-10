
#include <core/ext/Plugin.h>
#include <core/ext/Extension.h>

#include "ExtensionItemModel.h"

namespace Quartz { namespace Ext {

const int NUM_COLS = 3;

struct ExtensionItemModel::Data {
    Data()
        : m_extensions(nullptr) {
    }

    const ExtensionList* m_extensions;
};

ExtensionItemModel::ExtensionItemModel(QObject* parent)
    : QAbstractItemModel(parent)
    , m_data(std::make_unique<Data>()) {
}

ExtensionItemModel::~ExtensionItemModel() {
}

QModelIndex ExtensionItemModel::index(int row,
                                      int column,
                                      const QModelIndex& parent) const {
    auto index = QModelIndex();
    if (hasIndex(row, column, parent)) {
        const auto& ext = m_data->m_extensions->at(row);
        if (ext != nullptr) {
            index = createIndex(row, column, ext.get());
        }
    }
    return index;
}

QModelIndex ExtensionItemModel::parent(const QModelIndex& /*child*/) const {
    return QModelIndex();
}

int ExtensionItemModel::rowCount(const QModelIndex& /*parent*/) const {
    auto size = m_data->m_extensions != nullptr ? m_data->m_extensions->size()
                                                : 0;
    return size;
}

int ExtensionItemModel::columnCount(const QModelIndex& /*parent*/) const {
    return NUM_COLS;
}

QVariant ExtensionItemModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || m_data->m_extensions == nullptr
        || index.row() >= m_data->m_extensions->size()) {
        return QVariant();
    }
    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignLeft | Qt::AlignVCenter);
    } else if (role == Qt::DisplayRole) {
        const auto& ext = m_data->m_extensions->at(index.row());
        switch (index.column()) {
        case 0: return ext->extensionType();
        case 1: return ext->extensionId();
        case 2: return ext->extensionName();
        }
    }
    return QVariant();
}

bool ExtensionItemModel::hasChildren(const QModelIndex& parent) const {
    if (parent.isValid()) {
        return false;
    }
    return true;
}

QVariant ExtensionItemModel::headerData(int section,
                                        Qt::Orientation /*orientation*/,
                                        int role) const {
    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignLeft | Qt::AlignVCenter);
    } else if (role == Qt::DisplayRole) {
        switch (section) {
        case 0: return tr("Type");
        case 1: return tr("Id");
        case 2: return tr("Name");
        }
    }
    return QVariant();
}

void ExtensionItemModel::clear() {
    beginResetModel();
    m_data->m_extensions = nullptr;
    endResetModel();
}

void ExtensionItemModel::setExtensionList(const ExtensionList* extensions) {
    beginResetModel();
    m_data->m_extensions = extensions;
    endResetModel();
}

}} // namespace Quartz::Ext
