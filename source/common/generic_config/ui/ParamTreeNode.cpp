
#include <QVariant>

#include "../model/Param.h"
#include "ParamTreeNode.h"

namespace Quartz {

struct ParamTreeNode::Data
{
    Data( ITreeNode *parent,
          Param *param,
          QVariant value )
        : m_parent{ parent }
        , m_param{ param }
        , m_selected{ false }
    {

    }

    ITreeNode *m_parent;

    Param *m_param;

    bool m_selected;
};

ParamTreeNode::ParamTreeNode( ITreeNode *parent,
                              Param *param,
                              QVariant value )
    : m_data{ new Data{ parent, param, value }}
{

}

ParamTreeNode::~ParamTreeNode()
{

}

int ParamTreeNode::numChildren() const
{
    return 0;
}

int ParamTreeNode::numFields() const
{
    return 3;
}

ITreeNode * ParamTreeNode::child( int /*row*/ ) const
{
    return nullptr;
}

QVariant ParamTreeNode::data( int column ) const
{
    switch( column ) {
    case 0: return m_data->m_param->id();
    case 1: return m_data->m_param->name();
    case 2: return m_data->m_param->value();
    }
    return QVariant{};
}

void ParamTreeNode::setSelected( bool value )
{
    m_data->m_selected = value;
}

bool ParamTreeNode::isSelected() const
{
    return m_data->m_selected;
}

ITreeNode * ParamTreeNode::parent() const
{
    return m_data->m_parent;
}

int ParamTreeNode::indexOfChild( const ITreeNode */*child*/ ) const
{
    return -1;
}

bool ParamTreeNode::isEditable( int column ) const
{
    bool editable = false;
    if( column == 2 ) {
        editable = true;
    }
    return editable;
}

void ParamTreeNode::setData( int column, const QVariant &data )
{
    if( column == 2 ) {
        m_data->m_param->setValue( data );
    }
}

void ParamTreeNode::addChild( std::shared_ptr< ITreeNode > /*child*/ )
{

}

void ParamTreeNode::removeChild( const ITreeNode */*child*/ )
{

}

Param * ParamTreeNode::param() const
{
    return m_data->m_param;
}

}
