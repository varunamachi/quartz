
#include <QVector>
#include <QVariant>

#include "../model/Config.h"
#include "ConfigTreeNode.h"
#include "ParamTreeNode.h"
#include "GroupTreeNode.h"

namespace Quartz {

struct ConfigTreeNode::Data
{
    Data( TreeNode *parent,
          Config *config)
        : m_parent{ parent }
        , m_config{ config }
        , m_selected{ false }
    {

    }

    TreeNode *m_parent;

    Config *m_config;

    QVariant m_value;

    bool m_selected;

    QVector< std::shared_ptr< TreeNode >> m_children;
};

ConfigTreeNode::ConfigTreeNode( TreeNode *parent,
                                Config *config)
    : m_data{ new Data{ parent, config }}
{

}

ConfigTreeNode::~ConfigTreeNode()
{

}

int ConfigTreeNode::numChildren() const
{
    return m_data->m_config->numChildParams() + m_data->m_config->numGroups();
}

int ConfigTreeNode::numFields() const
{
    return 2;
}

bool ConfigTreeNode::isSelectable() const
{
    return false;
}

TreeNode * ConfigTreeNode::child( int row ) const
{
    std::shared_ptr< TreeNode > child;
    if( row < m_data->m_children.size() ) {
        child = m_data->m_children.at( row );
    }
    else {
        if( row < m_data->m_config->numChildParams() ) {
            auto *param = m_data->m_config->childParamAt( row );
            ///TODO somehow need to remove the const_cast below
            child = std::make_shared< ParamTreeNode >(
                        const_cast< ConfigTreeNode *>( this ),
                        param,
                        QVariant{} );
        }
        else if( row < m_data->m_config->numGroups() ){
            ///TODO somehow need to remove the const_cast below
            auto *group = m_data->m_config->groupAt( row );
            child = std::make_shared< GroupTreeNode >(
                        const_cast< ConfigTreeNode *>( this ),
                        group );
        }
        m_data->m_children.append( child );
    }
    return child.get();
}

QVariant ConfigTreeNode::data( int column ) const
{
    if( column == 0 ) {
        return m_data->m_config->name();
    }
    return QVariant{};
}

void ConfigTreeNode::setSelected( bool value )
{
    m_data->m_selected = value;
}

bool ConfigTreeNode::isSelected() const
{
    return m_data->m_selected;
}

TreeNode * ConfigTreeNode::parent() const
{
    return m_data->m_parent;
}

int ConfigTreeNode::indexOfChild( const TreeNode *child ) const
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

bool ConfigTreeNode::isEditable( int /*column*/ ) const
{
    return false;
}

void ConfigTreeNode::setData( int /*column*/, const QVariant &/*data*/ )
{
    //nothing here...
}

void ConfigTreeNode::addChild( std::shared_ptr< TreeNode > /*child*/ )
{
    //nothing here...
}

void ConfigTreeNode::removeChild( const TreeNode */*child*/ )
{
    //nothing here..
}

}
