#include "BooleanParam.h"

namespace Quartz {

BooleanParam::BooleanParam( const QString &id,
              const QString &name,
              const QString &category )
    : Param{ id, name, category }
    , m_default{ false }
{

}

void BooleanParam::setDefaultValue( bool value )
{
    m_default = value;
}

bool BooleanParam::defaultValue() const
{
    return m_default;
}

ParamType BooleanParam::type() const
{
    return ParamType::Boolean;
}

}
