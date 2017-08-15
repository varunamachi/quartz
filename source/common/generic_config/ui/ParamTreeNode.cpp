
#include <QVariant>

#include "ParamTreeNode.h"

namespace Quartz {

int ParamTreeNode::numChildren() const
{
    return 0;
}

int ParamTreeNode::numFields() const
{
    return 0;
}

ITreeNode * ParamTreeNode::child( int /*row*/ ) const
{
    return nullptr;
}

QVariant ParamTreeNode::data( int /*column*/ ) const
{
    return QVariant{};
}

void ParamTreeNode::setSelected( bool /*value*/ )
{

}

bool ParamTreeNode::isSelected() const
{
    return false;
}

ITreeNode * ParamTreeNode::parent() const
{
    return nullptr;
}

int ParamTreeNode::indexOfChild( const ITreeNode */*child*/ ) const
{
    return -1;
}

bool ParamTreeNode::isEditable( int /*column*/ ) const
{
    return false;
}

void ParamTreeNode::setData( int /*column*/, const QVariant &/*data*/ )
{

}

void ParamTreeNode::addChild( std::shared_ptr< ITreeNode > /*child*/ )
{

}

void ParamTreeNode::removeChild( const ITreeNode */*child*/ )
{

}

}
