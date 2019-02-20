#pragma once

#include<memory>

#include "Param.h"
#include "../../QuartzCommon.h"



namespace Quartz {

class QUARTZ_COMMON_API FixedParam : public Param
{
public:
    FixedParam(const QString &id,
               const QString &name,
               const QString &description,
               TreeNode *parent,
               const QVariant &value);

    ~FixedParam() override;

    QVariant value() const override;

    void setValue(const QVariant &value) override;

    ParamType type() const override;

    bool isEditable(int field) const override;

    std::unique_ptr<Param> clone() const override;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}
