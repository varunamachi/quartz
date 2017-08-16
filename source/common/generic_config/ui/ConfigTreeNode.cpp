
#include <QVector>
#include <QVariant>

#include "ConfigTreeNode.h"

namespace Quartz {

struct ConfigTreeNode::Data
{
    Data( ITreeNode *parent,
          Config *config)
        : m_parent{ parent }
        , m_config{ config }
        , m_selected{ false }
    {

    }

    ITreeNode *m_parent;

    Config *m_config;

    QVariant m_value;

    bool m_selected;

    QVector< std::shared_ptr< ITreeNode >> m_children;
};

ConfigTreeNode::ConfigTreeNode( ITreeNode *parent,
                                Config *config)
    : m_data{ new Data{ parent, config }}
{

}

ConfigTreeNode::~ConfigTreeNode()
{

}

int ConfigTreeNode::numChildren() const
{
    return 0;
}

int ConfigTreeNode::numFields() const
{
    return 0;
}

ITreeNode * ConfigTreeNode::child( int /*row*/ ) const
{
    return nullptr;
}

QVariant ConfigTreeNode::data( int /*column*/ ) const
{
    return QVariant{};
}

void ConfigTreeNode::setSelected( bool /*value*/ )
{

}

bool ConfigTreeNode::isSelected() const
{
    return false;
}

ITreeNode * ConfigTreeNode::parent() const
{
    return nullptr;
}

int ConfigTreeNode::indexOfChild( const ITreeNode */*child*/ ) const
{
    return -1;
}

bool ConfigTreeNode::isEditable( int /*column*/ ) const
{
    return false;
}

void ConfigTreeNode::setData( int /*column*/, const QVariant &/*data*/ )
{

}

void ConfigTreeNode::addChild( std::shared_ptr< ITreeNode > /*child*/ )
{

}

void ConfigTreeNode::removeChild( const ITreeNode */*child*/ )
{

}

}
