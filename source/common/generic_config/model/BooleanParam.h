#pragma once

#include "../../QuartzCommon.h"

#include "Param.h"

namespace Quartz {

class QUARTZ_COMMON_API BooleanParam : public Param
{
public:
    BooleanParam( const QString &id,
                  const QString &name,
                  const QString &description,
                  TreeNode *parent );

    ~BooleanParam();

    void setDefaultValue( bool value );

    bool defaultValue() const;

    ParamType type() const override;

    QVariant value() const override;

    void setValue( const QVariant &value ) override;

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

}
