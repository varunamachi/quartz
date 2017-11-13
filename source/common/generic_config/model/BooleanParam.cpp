#include <QVariant>

#include "BooleanParam.h"

namespace Quartz {

struct BooleanParam::Data
{
    explicit Data( bool def )
        : m_default{ def }
        , m_value{ def }
    {

    }

    bool m_default;

    bool m_value;
};

BooleanParam::BooleanParam(
        const QString &id,
        const QString &name,
        const QString &description,
        TreeNode *parent )
    : Param{ id, name, description, parent }
    , m_data{ new Data{ false }}
{

}

BooleanParam::~BooleanParam()
{

}

void BooleanParam::setDefaultValue( bool value )
{
    m_data->m_default = value;
}

bool BooleanParam::defaultValue() const
{
    return m_data->m_default;
}

ParamType BooleanParam::type() const
{
    return ParamType::Boolean;
}

QVariant BooleanParam::value() const
{
    return QVariant{ m_data->m_value };
}

void BooleanParam::setValue( const QVariant &value )
{
    if( value.isValid() ) {
        m_data->m_value = value.toBool();
    }
}

}
