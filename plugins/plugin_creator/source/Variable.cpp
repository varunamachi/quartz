#include <QString>
#include <QVariant>

#include "Variable.h"

namespace Quartz { namespace Plugin { namespace Creator {

struct Variable::Data
{
    Data( const QString &name,
          const QString &description,
          const QString &value )
        : m_name( name )
        , m_description( description )
        , m_value( value )
    {

    }

    QString m_name;

    QString m_description;

    QString m_value;

    bool m_isSelected;
};

Variable::Variable( const QString& name,
                    const QString& description,
                    const QString& value )
    : m_data{ new Data{ name, description, value }}
{

}

Variable::~Variable()
{

}

const QString&Variable::name() const
{
    return m_data->m_name;
}

const QString&Variable::value() const
{
    return m_data->m_value;
}

const QString&Variable::description() const
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

bool Variable::isSelected()
{
    return m_data->m_isSelected;
}


} } }
