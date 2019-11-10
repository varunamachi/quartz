#pragma once

#include <memory>

#include <QMetaType>
#include <QVariant>

#include "../QuartzCommon.h"

class QVariant;
class QString;

namespace Quartz {

class QUARTZ_COMMON_API TreeNode {
public:
    TreeNode(int numFields, TreeNode* parent = nullptr);

    TreeNode(const TreeNode& other);

    virtual ~TreeNode();

    virtual int numFields() const;

    virtual void setSelected(bool value);

    virtual bool isSelected() const;

    virtual int numChildren() const;

    virtual TreeNode* child(int row) const;

    virtual TreeNode* parent() const;

    void setParent(TreeNode* parent);

    virtual int indexOfChild(const TreeNode* child) const;

    virtual bool isEditable(int column) const;

    virtual bool setData(int column, const QVariant& data);

    virtual void addChild(TreeNode* child);

    virtual void removeChild(TreeNode* child);

    virtual QVariant decoration(int column) const;

    virtual QVariant fieldValue(int column) const = 0;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

template <typename T>
T treenode_cast(const QVariant& var) {
    auto tn = var.value<TreeNode*>();
    return dynamic_cast<T>(tn);
}

} // namespace Quartz

Q_DECLARE_METATYPE(Quartz::TreeNode*)
