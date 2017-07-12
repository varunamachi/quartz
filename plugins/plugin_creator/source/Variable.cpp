#include <QString>
#include <QVariant>

#include "Variable.h"

namespace Quartz { namespace Plugin { namespace Creator {

struct Variable::Data
{
    Data( const QString &name,
          const QString &description,
          const QString &value,
          ITreeNode *parent,
          bool selected )
        : m_name( name )
        , m_description( description )
        , m_value( value )
        , m_parent{ parent }
        , m_isSelected{ selected }
    {

    }

    QString m_name;

    QString m_description;

    QString m_value;

    ITreeNode *m_parent;

    bool m_isSelected;
};

Variable::Variable( const QString &name,
                    const QString &description,
                    const QString &value,
                    ITreeNode *parent,
                    bool selected )
    : m_data{ new Data{ name, description, value, parent, selected }}
{

}

Variable::~Variable()
{

}

const QString & Variable::name() const
{
    return m_data->m_name;
}

const QString & Variable::value() const
{
    return m_data->m_value;
}

const QString & Variable::description() const
{
    return m_data->m_description;
}

int Variable::numChildren() const
{
    return 0;
}

int Variable::numFields() const
{
    return 3;
}

ITreeNode * Variable::child( int /*row*/ ) const
{
    return nullptr;
}

QVariant Variable::data( int column ) const
{
    switch( column ) {
    case 0: return m_data->m_isSelected;
    case 1: return m_data->m_name;
    case 2: return m_data->m_value;
    }
    return "";
}

void Variable::setSelected( bool value )
{
    m_data->m_isSelected = value;
}

bool Variable::isSelected() const
{
    return m_data->m_isSelected;
}

ITreeNode *Variable::parent() const
{
    return m_data->m_parent;
}

int Variable::indexOfChild( const ITreeNode */*child*/ ) const
{
    //There are no children of variable, hence -1
    return -1;
}


} } }
