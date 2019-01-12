
#include <QVector>

#include "TreeNode.h"
#include "ArrayModel.h"

namespace Quartz {

struct ArrayModel::Data
{
    QVector< TreeNode *> m_roots;
};

ArrayModel::ArrayModel(
        int numFields,
        bool selectable,
        bool isFlat,
        const QVector<QString> &headers,
        QObject *parent)
    : AbstractTreeModel{
          parent,
          AbstractTreeModel::Options(numFields, selectable, isFlat, headers)}
    , m_data{ new Data{} }
{

}

ArrayModel::~ArrayModel()
{

}

TreeNode * ArrayModel::rootAt(int rowIndex) const
{
    TreeNode *root = nullptr;
    if (rowIndex < m_data->m_roots.size()) {
        root = m_data->m_roots.at(rowIndex);
    }
    return root;
}

int ArrayModel::rootCount() const
{
    return m_data->m_roots.size();
}

void ArrayModel::addRoot(TreeNode *node)
{
        beginResetModel();
        m_data->m_roots.push_back(node);
        endResetModel();
}

void ArrayModel::removeRoot(TreeNode *node)
{
        beginResetModel();
        m_data->m_roots.removeAll(node);
        endResetModel();
}

bool ArrayModel::contains(TreeNode *node)
{
    return m_data->m_roots.contains(node);
}

void ArrayModel::clear()
{
    beginResetModel();
    m_data->m_roots.clear();
    endResetModel();
}

}
