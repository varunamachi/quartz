#pragma once

#include "../../model_view/TreeNode.h"
#include "../../QuartzCommon.h"

namespace Quartz {

class Group;

class QUARTZ_COMMON_API GroupTreeNode : public TreeNode
{
public:
    GroupTreeNode( TreeNode *parent,
                   Group *group );

    ~GroupTreeNode();

    int numChildren() const override;

    int numFields() const override;

    bool isSelectable() const override;

    TreeNode * child( int row ) const override;

    QVariant data( int column ) const override;

    void setSelected( bool value ) override;

    bool isSelected() const override;

    TreeNode * parent() const override;

    int indexOfChild( const TreeNode *child ) const override;

    bool isEditable( int column ) const override;

    void setData( int column, const QVariant &data ) override;

    void addChild( std::shared_ptr< TreeNode > child ) override;

    void removeChild( const TreeNode *child ) override;

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

}
