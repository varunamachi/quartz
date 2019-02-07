#include <QVariant>

#include "BooleanParam.h"

namespace Quartz {

struct BooleanParam::Data
{
    explicit Data(bool def)
        : m_default(def)
        , m_value(def)
    {

    }

    bool m_default;

    bool m_value;
};

BooleanParam::BooleanParam(
        const QString &id,
        const QString &name,
        const QString &description,
        TreeNode *parent)
    : Param(id, name, description, parent)
    , m_data(std::make_unique<Data>(false))
{

}

BooleanParam::~BooleanParam()
{

}

void BooleanParam::setDefaultValue(bool value)
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

void BooleanParam::setValue(const QVariant &value)
{
    if (value.isValid()) {
        m_data->m_value = value.toBool();
    }
}

std::unique_ptr<Param> BooleanParam::clone() const
{
    auto param = std::make_unique<BooleanParam>(
                id(), name(), description(), parent());
    param->setDefaultValue(this->defaultValue());
    return std::move(param);
}

}
