#pragma once

#include <memory>

class QVariant;
class QString;

namespace Quartz {

class TreeNode
{
public:
    TreeNode(int numFields, TreeNode *parent = nullptr);

    virtual int numFields() const;

    virtual void setSelected(bool value);

    virtual bool isSelected() const;

    virtual int numChildren() const;

    virtual TreeNode * child(int row) const;

    virtual TreeNode * parent() const;

    void setParent(TreeNode *parent);

    virtual int indexOfChild(const TreeNode *child) const;

    virtual bool isEditable(int column) const;

    virtual bool setData(int column, const QVariant &data);

    virtual void addChild(TreeNode *child);

    virtual void removeChild(TreeNode *child);

    virtual QVariant fieldValue(int column) const = 0;

    virtual ~TreeNode();

private:
    struct Data;
    std::unique_ptr<Data> m_data;

};

}
