#pragma once

#include "Param.h"

namespace Quartz {

class BooleanParam : public Param
{
public:
    BooleanParam( const QString &id,
                  const QString &name,
                  const QString &category );

    void setDefaultValue( bool value );

    bool defaultValue() const;

    ParamType type() const override;

private:
    bool m_default;

};

}
