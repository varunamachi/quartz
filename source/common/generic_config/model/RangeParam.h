#pragma once

#include "Param.h"

#include "../../QuartzCommon.h"

class QString;

namespace Quartz {

class QUARTZ_COMMON_API RangeParam : public Param
{
public:
    RangeParam(const QString &id,
                const QString &name,
                const QString &description,
                TreeNode *parent);

    ~RangeParam();

    int maxVal() const;

    void setMax(int max);

    int minVal() const;

    void setMin(int min);

    int inc() const;

    void setIncrement(int inc);

    int defaultValue() const;

    void setDefaultValue(int defaultValue);

    ParamType type() const override;

    QVariant value() const override;

    void setValue(const QVariant &value) override;

    std::unique_ptr<Param> clone() const;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}
