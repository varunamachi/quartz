#include <QSize>

#include "TreeNode.h"
#include "AbstractTreeModel.h"


namespace Quartz {

struct AbstractTreeModel::Data
{
    Data(Options opts)
        : m_numFields{ opts.numFields }
        , m_selectable{ opts.selectable }
        , m_isFlat{ opts.flat }
        , m_headers{ opts.headers }
    {
        if (m_selectable) {
            ++ m_numFields;
        }
    }

    int m_numFields;

    bool m_selectable;

    bool m_isFlat;

    QVector<QString> m_headers;
};

AbstractTreeModel::AbstractTreeModel(QObject *parent, Options opts)
    : QAbstractItemModel(parent)
    , m_data(std::make_unique<Data>(opts))
{

}
//AbstractTreeModel::AbstractTreeModel(
//        int numFields,
//        bool selectable,
//        bool flat,
//        const QVector<QString> &headers,
//        QObject *parent)
//    : QAbstractItemModel(parent)
//    , m_data(std::make_unique<Data>(selectable, numFields, flat, headers))
//{

//}

bool isBool(const QVariant &var) {
    return var.type() == QVariant::Bool;
}


AbstractTreeModel::~AbstractTreeModel()
{

}

QModelIndex AbstractTreeModel::index(int row,
                                      int column,
                                      const QModelIndex &parent) const
{
    QModelIndex index;
    if (! hasIndex(row, column, parent)) {
        return index;
    }
    if (! m_data->m_isFlat && parent.isValid()) {
        auto node = static_cast<TreeNode * >(parent.internalPointer());
        auto child = node->child(row);
        if (child != nullptr) {
            index = createIndex(row, column, child);
        }
    } else {
        auto node = rootAt(row);
        if (node != nullptr) {
            index = createIndex(row, column, node);
        }
    }
    return index;
}

QModelIndex AbstractTreeModel::parent(const QModelIndex& childIndex) const
{
    if (m_data->m_isFlat || ! childIndex.isValid()) {
        return QModelIndex{};
    }
    auto index = QModelIndex{};
    auto node = static_cast<TreeNode *>(childIndex.internalPointer());
    if (node != nullptr && node->parent() != nullptr) {
        auto parent = node->parent();
        auto grandParent = parent->parent();
        auto row = 0;
        if (grandParent != nullptr) {
            row = grandParent->indexOfChild(parent);
        }
        if (row != -1) {
            //only zeroth column ??
            index = createIndex(row, 0, parent);
        }
    }
    return index;
}

int AbstractTreeModel::rowCount(const QModelIndex& parent) const
{
    auto count = rootCount();
    if (! m_data->m_isFlat && parent.isValid()) {
        auto node = static_cast<TreeNode *>(parent.internalPointer());
        count = node->numChildren();
    }
    return count;
}

int AbstractTreeModel::columnCount(const QModelIndex& /*parent*/) const
{
    return m_data->m_numFields;
}

QVariant AbstractTreeModel::data(const QModelIndex& index,
                                  int role) const
{
    auto node = static_cast<TreeNode *>(index.internalPointer());
    if (index.isValid() && node != nullptr) {
        auto col = m_data->m_selectable ? index.column() - 1 : index.column();
        if (m_data->m_selectable && index.column() == 0){
            switch(role) {
            case Qt::CheckStateRole:
                return node->isSelected() ? Qt::Checked : Qt::Unchecked;
            case Qt::DisplayRole:
            case Qt::EditRole:
                return "";
            }
            return QVariant{};
        }
        auto data = node->fieldValue(col);
        if (isBool(data)) {
            switch(role) {
            case Qt::CheckStateRole:
                return data.toBool() ? Qt::Checked : Qt::Unchecked;
            case Qt::DisplayRole:
            case Qt::EditRole:
                return "";
            }
            return QVariant{};
        }
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            return data;
        }
        if (role == Qt::UserRole) {
            return QVariant::fromValue(node);
        }
        if (role == Qt::DecorationRole) {
            return node->decoration(col);
        }
    }
    return QVariant{};
}

QVariant AbstractTreeModel::headerData(int section,
                                        Qt::Orientation o,
                                        int role) const
{
    if (o == Qt::Horizontal && role == Qt::DisplayRole) {
        if (m_data->m_selectable && section == 0) {
            return QLatin1Literal("Select");
        }
        auto col = m_data->m_selectable ? section - 1 : section;
        if (col < m_data->m_headers.size()) {
            return m_data->m_headers.at(col);
        }
    }
    return QVariant{};
}

bool AbstractTreeModel::hasChildren(const QModelIndex& parent) const
{
    auto has = rootCount() != 0;
    if (parent.isValid()) {
        if (m_data->m_isFlat) {
            has = false;
        } else {
            auto node = static_cast<TreeNode *>(parent.internalPointer());
            has = node->numChildren() != 0;
        }
    }
    return has;
}

bool AbstractTreeModel::setData(const QModelIndex &index,
                                 const QVariant &value,
                                 int role)
{
    bool set = false;
    TreeNode *node = nullptr;
    if (index.isValid()) {
        node = static_cast<TreeNode *>(index.internalPointer());
        if (node != nullptr) {
            auto col = m_data->m_selectable ? index.column() - 1
                                            : index.column();
            if (role == Qt::CheckStateRole) {
                auto val = value.toInt() == Qt::Checked;
                if (m_data->m_selectable && index.column() == 0) {
                    node->setSelected(val);
                    set = true;
                }
                else {
                    set = node->setData(col, val);
                }
            }
            else if (role == Qt::EditRole
                     && ! isBool(node->fieldValue(col))) {
                set = node->setData(col, value);
            }
        }
    }
    if (set) {
        emit dataChanged(index, index);
    }
    return set;
}

Qt::ItemFlags AbstractTreeModel::flags(const QModelIndex &index) const
{
    auto node = static_cast<TreeNode *>(index.internalPointer());
    if (! index.isValid() || node == nullptr) {
        return Qt::NoItemFlags;
    }
    auto col = m_data->m_selectable ? index.column() - 1 : index.column();
    auto flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if (m_data->m_selectable && index.column() == 0) {
        return flags | Qt::ItemIsUserCheckable;
    }
    if (isBool(node->fieldValue(col)) && node->isEditable(col)) {
        return flags | Qt::ItemIsUserCheckable;
    }
    if (node->isEditable(col)) {
        return flags | Qt::ItemIsEditable;
    }
    return flags;
}


}
