
#include <QVariant>

#include "ConfigTreeNode.h"

namespace Quartz {

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
