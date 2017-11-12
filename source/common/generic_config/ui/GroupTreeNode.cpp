
#include <QVariant>
#include <QVector>

#include "../model/Group.h"
#include "../model/Param.h"

#include "ParamTreeNode.h"
#include "GroupTreeNode.h"

namespace Quartz {

struct GroupTreeNode::Data
{
    Data( TreeNode *parent,
          Group *group )
        : m_parent{ parent }
        , m_group{ group }
        , m_selected{ false }
    {

    }

    TreeNode *m_parent;

    Group *m_group;

    QVariant m_value;

    bool m_selected;

    QVector< std::shared_ptr< TreeNode >> m_children;
};

GroupTreeNode::GroupTreeNode( TreeNode *parent,
                              Group *group )
    : m_data{ new Data{ parent, group }}
{

}

GroupTreeNode::~GroupTreeNode()
{

}

int GroupTreeNode::numChildren() const
{
    return m_data->m_group->numParams() + m_data->m_group->numSubGroups();
}

int GroupTreeNode::numFields() const
{
    return 2;
}

bool GroupTreeNode::isSelectable() const
{
    return false;
}

TreeNode * GroupTreeNode::child( int row ) const
{
    std::shared_ptr< TreeNode > child;
    if( row > m_data->m_children.size() ) {
        if( row < m_data->m_group->numParams() ) {
            auto *param = m_data->m_group->paramAt( row );
            ///TODO somehow need to remove the const_cast below
            child = std::make_shared< ParamTreeNode >(
                        const_cast< GroupTreeNode *>( this ),
                        param,
                        QVariant{} );
        }
        else if( row < m_data->m_group->numSubGroups() ){
            ///TODO somehow need to remove the const_cast below
            auto *group = m_data->m_group->subGroupAt( row );
            child = std::make_shared< GroupTreeNode >(
                        const_cast< GroupTreeNode *>( this ),
                        group );
        }
    }
    else {
        child = m_data->m_children.at( row );
    }
    return child.get();
}

QVariant GroupTreeNode::data( int column ) const
{
    switch( column ) {
    case 0: return m_data->m_group->id();
    case 1: return m_data->m_group->name();
    }
    return QVariant{};
}

void GroupTreeNode::setSelected( bool value )
{
    m_data->m_selected = value;
}

bool GroupTreeNode::isSelected() const
{
    return m_data->m_selected;
}

TreeNode * GroupTreeNode::parent() const
{
    return m_data->m_parent;
}

int GroupTreeNode::indexOfChild( const TreeNode *child ) const
{
    //Should we create all the children??
    auto index = -1;
    for( auto i = 0; i < m_data->m_children.size(); ++ i  ) {
        auto ch = m_data->m_children.at( i ).get();
        if( ch == child ) {
            index = i;
            break;
        }
    }
    return index;
}

bool GroupTreeNode::isEditable( int /*column*/ ) const
{
    return false;
}

void GroupTreeNode::setData( int /*column*/, const QVariant &/*data*/ )
{
    //nothing here...
}

void GroupTreeNode::addChild( std::shared_ptr< TreeNode > /*child*/ )
{
    //nothing here...
}

void GroupTreeNode::removeChild( const TreeNode */*child*/ )
{
    //nothing here...
}

}
