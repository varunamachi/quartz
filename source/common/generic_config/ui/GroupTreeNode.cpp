
#include <QVariant>

#include "GroupTreeNode.h"

namespace Quartz {

int GroupTreeNode::numChildren() const
{
    return 0;
}

int GroupTreeNode::numFields() const
{
    return 0;
}

ITreeNode * GroupTreeNode::child( int /*row*/ ) const
{
    return nullptr;
}

QVariant GroupTreeNode::data( int /*column*/ ) const
{
    return QVariant{};
}

void GroupTreeNode::setSelected( bool /*value*/ )
{

}

bool GroupTreeNode::isSelected() const
{
    return false;
}

ITreeNode * GroupTreeNode::parent() const
{
    return nullptr;
}

int GroupTreeNode::indexOfChild( const ITreeNode */*child*/ ) const
{
    return -1;
}

bool GroupTreeNode::isEditable( int /*column*/ ) const
{
    return false;
}

void GroupTreeNode::setData( int /*column*/, const QVariant &/*data*/ )
{

}

void GroupTreeNode::addChild( std::shared_ptr< ITreeNode > /*child*/ )
{

}

void GroupTreeNode::removeChild( const ITreeNode */*child*/ )
{

}

}
