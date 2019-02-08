#pragma once

#include <QPair>

#include "../../QuartzCommon.h"
#include "Param.h"

namespace Quartz {

class QUARTZ_COMMON_API ChoiceParam : public Param
{
public:
    explicit ChoiceParam(const QString &id,
                         const QString &name,
                         const QString &description,
                         TreeNode *parent);

    ~ChoiceParam() override;

    void addOption(const QString &name, const QVariant &value);

    QPair<QString, QVariant> option(int index) const;

    int defaultIndex() const;

    void setDefaultIndex(int defaultIndex);

    void setDefaultValue(const QVariant &value);

    int numOption() const;

    ParamType type() const override;

    QVariant value() const override;

    int index() const;

    void setValue(const QVariant &value) override;

    std::unique_ptr<Param> clone() const override;

    QVariant fieldValue(int field) const override;

private:
    struct Data;
    std::unique_ptr<Data> m_data;

};

}
