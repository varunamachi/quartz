
#include <QVariant>

#include "../model/Param.h"
#include "../model/ChoiceParam.h"
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
    return 2;
}

bool ParamTreeNode::isSelectable() const
{
    return false;
}

ITreeNode * ParamTreeNode::child( int /*row*/ ) const
{
    return nullptr;
}

QVariant ParamTreeNode::data( int column ) const
{
    switch( column ) {
    case 0: return m_data->m_param->id();
    case 1: {
        if( m_data->m_param->type() == ParamType::Choice ) {
            auto cp = static_cast< ChoiceParam *>( m_data->m_param );
            return cp->option( cp->index() ).first;
        }
        else {
            return m_data->m_param->value();
        }
    }
    case 2: return m_data->m_param->name();
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
    if( column == 1 ) {
        editable = true;
    }
    return editable;
}

void ParamTreeNode::setData( int column, const QVariant &data )
{
    if( column == 1 ) {
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
