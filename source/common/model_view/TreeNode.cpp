
#include <QVector>

#include "TreeNode.h"

namespace Quartz {

struct TreeNode::Data
{
    Data( int numFields,
          bool selectable,
          TreeNode *parent )
        : m_numFields{ numFields }
        , m_isSelectable{ selectable }
        , m_selected{ false }
        , m_parent{ parent }
    {

    }

    int m_numFields;

    bool m_isSelectable;

    bool m_selected;

    TreeNode * m_parent;

    QVector< TreeNode *> m_children;
};

TreeNode::TreeNode(
        int numFields,
        bool isSelectable,
        TreeNode *parent )
    : m_data{ new Data{ numFields, isSelectable, parent }}
{

}

int TreeNode::numFields() const
{
    return m_data->m_numFields;
}

bool TreeNode::isSelectable() const
{
    return m_data->m_isSelectable;
}

void TreeNode::setSelected( bool value )
{
    m_data->m_selected = value;
}

bool TreeNode::isSelected() const
{
    return m_data->m_isSelectable && m_data->m_selected;
}

int TreeNode::numChildren() const
{
    return m_data->m_children.size();
}

TreeNode * TreeNode::child( int row ) const
{
    TreeNode *child = nullptr;
    if( row < m_data->m_children.size() ) {
        child = m_data->m_children.at( row );
    }
    return child;
}

TreeNode * TreeNode::parent() const
{
    return m_data->m_parent;
}

void TreeNode::setParent( TreeNode *parent )
{
    m_data->m_parent = parent;
}

int TreeNode::indexOfChild( const TreeNode *child ) const
{
    auto index = -1;
    for( auto i = 0; i < m_data->m_children.size(); ++ i  ) {
        auto ch = m_data->m_children.at( i );
        if( ch == child ) {
            index = i;
            break;
        }
    }
    return index;
}

bool TreeNode::isEditable( int /*column*/ ) const
{
    //Default impl, nothing is editable
    return false;
}

void TreeNode::setData( int /*column*/, const QVariant &/*data*/ )
{
    //Default implementation does not do anything...
}

void TreeNode::addChild( TreeNode *child )
{
    if( child != nullptr ) {
        m_data->m_children.append( child );
    }
}

void TreeNode::removeChild( TreeNode *child )
{
    m_data->m_children.removeAll( child );
}

}
